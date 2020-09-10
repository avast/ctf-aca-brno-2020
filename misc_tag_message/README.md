# Tag Message (Misc #10)

## Description
```
We have information that you received a tag with super secret data. It should be on you right now. Find it, and retrieve the data.
```

## Solution

Each participant obtained a badge with NFC tag NTAG216 in it. Flag was inserted between random chars with a pattern of PI number ( 3141592653589793238462... ), split to 3 or 4 chunks (based on number of team members), base64 encoded and written to NFC tag. By reversing this process, the team could obtain a flag. 

---

PI pattern explained - we have got string `abcFdLefghAiG` which when we put to the PI pattern

| 3   | flag | 1 | flag | 4    | flag | 1 | flag |
| --- | ---- | - | ---- | ---- | ---- | - | ---- |
| abc | `F`  | d | `L`  | efgh | `A`  | i | `G`  |

we can see that flag is `FLAG` and in this case alphabet between represents random characters.

---