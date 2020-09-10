from gtts import gTTS

FLAG = "avastCTF opening curly bracket l 3 f t_t h 1 s_f 0 r_y 0 u_h 3 r e closing curly bracket"

tts = gTTS(FLAG, slow=True)
tts.save("flag.mp3")
