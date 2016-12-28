##Dragino device

In this section we will show how to connect a dragino ms14 to our system by Internet to get control over gpios remotely.

- First, you must get internet access from you dragino device, please read the documentation from here http://wiki.dragino.com/index.php?title=Getting_Start_with_Arduino_Yun

- Second obtain the info from "devinfo" button on www.redlibre.cl, you will see the following
```
 #define IOTUSERNAME "xxxxxxx"
 #define IOTPASSWORD "yyyyyyy"
 #define IOTDEVICE "zzzzzz"
 #define USERNAME "uuuuu"
```

`#define IOTUSERNAME "xxxxxxx"` means, the unique id give from our platform to your device, is automatic generated when you create a device first time

`#define IOTPASSWORD "yyyyyyy"` means the password that you entered when created the device.

`#define IOTDEVICE "zzzzzz"` means the name that you entered when created the device.

`#define USERNAME "uuuuu"` is your username


- Third, get the sketch from here and modify the part thats say

```
////Please here paste info from "devinfo"//////////
#define IOTUSERNAME "xxxxxxx"
#define IOTPASSWORD "yyyyyyy"
#define IOTDEVICE "zzzzzz"
#define USERNAME "uuuuu"
///////////////////////////////////////////////////
```

with the info provided from devinfo web page


upload the sketch.ino into dragino by IP using ide 1.6.7
