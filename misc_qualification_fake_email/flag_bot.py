import httplib2
import os
import re
import oauth2client
import base64
import time
import random
import logging

from oauth2client import client, tools, file
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from apiclient import errors, discovery

SCOPES = 'https://mail.google.com/'
CLIENT_SECRET_FILE = 'credentials.json'
APPLICATION_NAME = 'Gmail API Python Send Email'

FLAGS = []

logger = logging.getLogger('flag_bot')
logger.setLevel(logging.DEBUG)
sh = logging.StreamHandler()
fh = logging.FileHandler('flag_bot.log')
formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
sh.setFormatter(formatter)
fh.setFormatter(formatter)
logger.addHandler(sh)
logger.addHandler(fh)

def ListMessagesMatchingQuery(service, user_id, query=''):
    try:
        response = service.users().messages().list(userId=user_id,q=query).execute()
        messages = []
        if 'messages' in response:
            messages.extend(response['messages'])
        
        while 'nextPageToken' in response:
            page_token = response['nextPageToken']
            response = service.users().messages().list(userId=user_id, q=query,pageToken=page_token).execute()
            messages.extend(response['messages'])
        return messages
    except errors.HttpError as error:
        logger.error('An error occurred: %s' % error)

def GetMessage(service, user_id, msg_id):
    try:
        message = service.users().messages().get(userId=user_id, id=msg_id).execute()
        return message
    except errors.HttpError as error:
        logger.error('An error occurred: %s' % error)

def get_credentials():
    credential_path = 'gmail-python-email-send.json'
    store = oauth2client.file.Storage(credential_path)
    credentials = store.get()
    if not credentials or credentials.invalid:
        flow = client.flow_from_clientsecrets(CLIENT_SECRET_FILE, SCOPES)
        flow.user_agent = APPLICATION_NAME
        credentials = tools.run_flow(flow, store)
        logger.info('Storing credentials to ' + credential_path)
    return credentials  

def SendMessage(service, user_id, message):
    try:
        message = (service.users().messages().send(userId=user_id, body=message).execute())
        logger.info('Message Id: %s' % message['id'])
        return message
    except errors.HttpError as error:
        logger.error('An error occurred: %s' % error)

def CreateMessage(sender, to, subject, msgPlain):
    msg = MIMEMultipart('alternative')
    msg['Subject'] = subject
    msg['From'] = sender
    msg['To'] = to
    msg.attach(MIMEText(msgPlain, 'plain'))
    raw = base64.urlsafe_b64encode(msg.as_bytes())
    raw = raw.decode()
    body = {'raw': raw}
    return body

def findEmail(message):
    match = re.search(r'[\S\.-]+@[\w\.-]+', message)
    if match:
        return match.group(0)
    else:
        return 'No match'
    
def DeleteMessage(service, user_id, msg_id):
    try:
        service.users().messages().delete(userId=user_id, id=msg_id).execute()
        logger.info('Message with id: %s deleted successfully.' % msg_id)
    except errors.HttpError as error:
        logger.error('An error occurred: %s' % error)


def load_flags():
    with open('flags.txt') as data:
        for line in data:
            FLAGS.append(str(line.rstrip()))


def get_flag():
    flag = random.choice(FLAGS)
    FLAGS.remove(flag)
    return flag

def do_stuff():
    credentials = get_credentials()
    http = credentials.authorize(httplib2.Http())
    service = discovery.build('gmail', 'v1', http=http)
    inbox_ids = ListMessagesMatchingQuery(service,"me",'in:inbox')
    spam_ids = ListMessagesMatchingQuery(service,"me",'in:spam')
    message_ids = inbox_ids + spam_ids
    for message_id in message_ids:
        message = GetMessage(service, "me", message_id['id'])
        from_address = [value['value'] for value in message['payload']['headers'] if value['name'] == 'From'][0]
        snippet = message['snippet']
        logger.info(f'From: {from_address} | Body: {snippet}')
        send_flag_address = findEmail(snippet)
        if 'ca-participant@cyberadventurectf.com' in from_address and send_flag_address != 'No match':
            to = send_flag_address
            sender = "cyberadventurectf@gmail.com"
            subject = "Avast Cyber Adventure CTF Flag"
            flag = get_flag()
            msgPlain = f'I believe this should be yours {flag}'
            reply_message = CreateMessage(sender, to, subject, msgPlain)
            # SendMessage(service, "me", reply_message)
            logger.info(f'sent flag {flag} to {send_flag_address}')
        elif 'mailer-daemon@googlemail.com' in from_address or send_flag_address == 'No match':
            # passing email from mailer-daemon when someone put non existing email address
            # or email does not have send_flag_address
            logger.info(f'Skipping email from {from_address} - no email found.')
            pass
        else:
            to = send_flag_address
            sender = "cyberadventurectf@gmail.com"
            subject = "Do we know you?"
            msgPlain = "I am sorry but this must be some misunderstanding. We don't know who you are."
            reply_message = CreateMessage(sender, to, subject, msgPlain)
            # SendMessage(service, "me", reply_message)
            logger.info('sent no-flag to %s' % send_flag_address)
        # DeleteMessage(service,"me",message_id['id'])
   
def main():
    logger.info('Starting Flag Bot')
    load_flags()
    while True:
        do_stuff()
        time.sleep(30)

if __name__ == '__main__':
    main()