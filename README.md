# AndroidUtils
AndroidUtils is a small Qt library that can ease Android app development in QML

## Features
* Change status bar color (requires Android Platform 21+)
* Display toast popups (text only)
* Invoke "Share" menu (text only)

TODO: DP to Pixel conversion?

TODO: maybe some other stuff

## Integration
1. Include the library in your qmake \*.pro file:
```qmake
include("/path/to/lib/androidutils.pri")
```
2. Register the QML type:
```c++
#include "androidutils.h"

...

qmlRegisterType<AndroidUtils>("AndroidUtils", 1, 0, "AndroidUtils");
```

## Usage
```qml
import AndroidUtils 1.0

...

AndroidUtils {
    id: util

    // Set status bar color
    statusBarColor: Material.color(Material.Green, Material.Shade700)
}

...

// Short duration toast
onClicked: util.showShortToastMessage("Test")

// Long duration toast
onClicked: util.showLongToastMessage("Test")

...

// Share some text to other apps
onClicked: util.sharePlainText("Text to share", "Dialog title")

...

// Status bar color availability field
// False if Android Platform is too old or not running on Android
util.statusBarColorAvailable

// Utils availability field
// False if not running on Android
util.available

```
