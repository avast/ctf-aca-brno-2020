import time
import random

from selenium import webdriver


TEST_DATA = [
    # Valid
    {'username': 'loudRos355', 'password': 'mixopura82'},
    # Invalid
    {'username': 'admin', 'password': 'password'},
    {'username': 'admin', 'password': '123123'},
    {'username': 'lehunesa46', 'password': '123123'},
    {'username': 'vimufibo93', 'password': 'yoliwexo36'},
    {'username': 'guwiligi42', 'password': 'xihedigo19'},
]


def main():
    chrome_options = webdriver.ChromeOptions()
    chrome_options.add_argument('--no-sandbox')
    chrome_options.add_argument('--headless')
    chrome_options.add_argument('--disable-gpu')
    # Muy importante.
    chrome_options.add_argument('--ignore-certificate-errors')

    driver = webdriver.Chrome(options=chrome_options)
    driver.implicitly_wait(10)

    driver.get('https://vulnerable-webserver')

    username = driver.find_element_by_name('username')
    password = driver.find_element_by_name('password')

    [auth] = random.sample(TEST_DATA, 1)
    username.send_keys(auth['username'])
    password.send_keys(auth['password'])
    password.submit()

    driver.close()



if __name__ == '__main__':
    while True:
        main()
        time.sleep(20)
