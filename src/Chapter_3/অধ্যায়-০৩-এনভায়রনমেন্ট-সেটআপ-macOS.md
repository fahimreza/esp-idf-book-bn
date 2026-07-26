# অধ্যায় ৩: এনভায়রনমেন্ট সেটআপ (macOS)

## ৩.১ এই অধ্যায়ে আমরা কী শিখব?

দ্বিতীয় অধ্যায়ে আমরা Windows-এ ESP-IDF এনভায়রনমেন্ট সেটআপ করেছি। যারা macOS ব্যবহার করেন, তাদের জন্য এই অধ্যায়। মূল ধারণা একদম একই — শুধু ইনস্টলেশনের কমান্ড ও টুলগুলো macOS-এর উপযোগী।

> **নোট**: Windows অধ্যায়ের মতোই, এখানেও আমরা ইচ্ছাকৃতভাবে **Terminal-ভিত্তিক Legacy পদ্ধতি** (`install.sh` ও `export.sh` স্ক্রিপ্ট) ব্যবহার করব, EIM (ESP-IDF Installation Manager) না। এতে ESP-IDF-এর মূল কমান্ড-লাইন ওয়ার্কফ্লোটা স্পষ্টভাবে বোঝা যায়। Espressif-এর অফিসিয়াল ডকুমেন্টেশনে এই পদ্ধতিকে এখন "Legacy" হিসেবে চিহ্নিত করা হয়েছে (নতুন recommended পদ্ধতি হলো EIM), কিন্তু এটা এখনও পুরোপুরি কার্যকর এবং শেখার জন্য চমৎকার।

আমরা ধাপে ধাপে যা করব:

1. Visual Studio Code (VS Code) ইনস্টল করা
2. Prerequisites (Homebrew, Xcode Command Line Tools, CMake, Ninja ইত্যাদি) ইনস্টল করা
3. ESP-IDF ফ্রেমওয়ার্ক ইনস্টল করা
4. New Project তৈরি এবং বিল্ড করা
5. ESP32-তে প্রোগ্রাম আপলোড করা

---

## ৩.২ প্রয়োজনীয় জিনিসপত্র

পরবর্তী ধাপ শুরু করার আগে নিশ্চিত হয়ে নিন যে আপনার কাছে আছে:

- একটি Mac কম্পিউটার (macOS Monterey বা তার পরের ভার্সন সুপারিশকৃত)
- স্ট্যাবল ইন্টারনেট কানেকশন (ESP-IDF এবং এর টুলচেইন ডাউনলোড করতে 1-2 GB পর্যন্ত ডেটা লাগতে পারে)
- একটি ESP32 Dev Kit V1 বোর্ড এবং একটি ভালো মানের USB ক্যাবল (শুধু চার্জিং না, ডেটা ট্রান্সফার সাপোর্ট করে এমন ক্যাবল হতে হবে)
- আপনার Mac-এর অ্যাডমিন পাসওয়ার্ড (Xcode Command Line Tools ও Homebrew ইনস্টল করার সময় লাগবে)

---

## ৩.৩ ধাপ ১: Visual Studio Code ইনস্টল করা

যদি আপনার Mac-এ আগে থেকেই VS Code ইনস্টল করা না থাকে:

1. ব্রাউজারে যান **[code.visualstudio.com](https://code.visualstudio.com/)**-এ।
2. **Download for Mac** বাটনে ক্লিক করে `.zip` ফাইলটি ডাউনলোড করুন।
3. ডাউনলোড হওয়া ফাইলটি এক্সট্র্যাক্ট হলে **Visual Studio Code.app** ফাইলটি **Applications** ফোল্ডারে ড্র্যাগ করে নিন।
4. Launchpad বা Spotlight (`Cmd + Space` চেপে "VS Code" লিখে) থেকে VS Code চালু করুন।

*Figure: VS Code Download for Mac*

> **নোট**: প্রথমবার খুললে macOS একটা সিকিউরিটি ওয়ার্নিং দেখাতে পারে ("VS Code is an app downloaded from the Internet")। এটা স্বাভাবিক — **Open** বাটনে ক্লিক করলেই চলবে।

> **নোট**: Windows চ্যাপ্টারের মতোই, VS Code খুললে যদি পরিচিত হালকা রঙের থিমের বদলে নতুন গাঢ় থিম দেখতে পান, তাহলে **File > Preferences > Theme > Color Theme** (`Cmd+K Cmd+T`) থেকে পছন্দের থিম বেছে নিতে পারেন।

---

## ৩.৪ ধাপ ২: Prerequisites ইনস্টল করা

ESP-IDF কম্পাইল করার জন্য কিছু বেসিক টুল দরকার। প্রথমে Terminal খুলুন (Spotlight থেকে `Cmd + Space` চেপে "Terminal" লিখে সার্চ করুন)।

### ৩.৪.১ Xcode Command Line Tools ইনস্টল করা

Terminal-এ নিচের কমান্ডটি চালান:

```bash
xcode-select --install
```

একটা পপ-আপ উইন্ডো আসবে — **Install** বাটনে ক্লিক করে ইনস্টলেশন সম্পন্ন করুন। এতে কিছুটা সময় লাগতে পারে।

*Figure: Xcode Command Line Tools Install Popup*

> **নোট**: পরবর্তীতে কোনো ধাপে যদি `xcrun: error: invalid active developer path` এই ধরনের এরর দেখেন, তার মানে এই টুলগুলো ঠিকভাবে ইনস্টল হয়নি — আবার `xcode-select --install` চালান।

### ৩.৪.২ Homebrew ইনস্টল করা

**Homebrew** হলো macOS-এর জনপ্রিয় প্যাকেজ ম্যানেজার — এটা দিয়ে আমরা বাকি সব টুল ইনস্টল করব। যদি আগে থেকে ইনস্টল করা না থাকে, Terminal-এ চালান:

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

ইনস্টলেশনের সময় আপনার Mac-এর পাসওয়ার্ড চাইতে পারে — দিয়ে দিন। ইনস্টলেশন শেষে টার্মিনাল কিছু নির্দেশনা দেখাতে পারে (যেমন `PATH`-এ Homebrew যোগ করার কমান্ড) — সেগুলো কপি-পেস্ট করে চালিয়ে নিন।

*Figure: Homebrew Installation*

### ৩.৪.৩ CMake, Ninja, dfu-util, ccache ইনস্টল করা

```bash
brew install cmake ninja dfu-util ccache
```

*Figure: Installing Build Tools via Homebrew*

### ৩.৪.৪ Python ভার্সন যাচাই করা

ESP-IDF-এর জন্য Python 3.10 বা তার পরের ভার্সন লাগবে। macOS-এর built-in Python এতে যথেষ্ট না-ও হতে পারে, তাই যাচাই করে নিন:

```bash
python3 --version
```

যদি ভার্সন 3.10-এর কম দেখায়, Homebrew দিয়ে নতুন Python ইনস্টল করুন:

```bash
brew install python3
```

> **নোট (Apple Silicon — M1/M2/M3/M4 ইউজারদের জন্য)**: যদি পরবর্তীতে `bad CPU type in executable` জাতীয় এরর দেখেন, তাহলে Apple Rosetta 2 ইনস্টল করতে হবে:
> ```bash
> /usr/sbin/softwareupdate --install-rosetta --agree-to-license
> ```

---

## ৩.৫ ধাপ ৩: ESP-IDF ইনস্টল করা

### ৩.৫.১ ESP-IDF সোর্স কোড ডাউনলোড করা (Git Clone)

Terminal-এ নিচের কমান্ডগুলো একে একে চালান:

```bash
mkdir -p ~/esp
cd ~/esp
git clone -b v5.5.4 --recursive https://github.com/espressif/esp-idf.git
```

এতে GitHub থেকে ESP-IDF v5.5.4 (Windows চ্যাপ্টারে ব্যবহৃত একই ভার্সন, সামঞ্জস্যের জন্য) `~/esp/esp-idf` ফোল্ডারে ডাউনলোড হবে। এতে কিছুটা সময় লাগবে (ফাইল সাইজ বড়, সাব-মডিউলসহ)।

*Figure: Git Clone ESP-IDF*

### ৩.৫.২ টুলচেইন ইনস্টল করা

```bash
cd ~/esp/esp-idf
./install.sh esp32
```

এই কমান্ড কম্পাইলার, Python প্যাকেজ, এবং অন্যান্য প্রয়োজনীয় টুল ইনস্টল করবে। সফল হলে শেষে **"All done!"** জাতীয় মেসেজ দেখতে পাবেন।

*Figure: Running install.sh*

> **নোট**: যদি `SSL: CERTIFICATE_VERIFY_FAILED` জাতীয় এরর দেখেন, আপনার Python ফোল্ডারে থাকা `Install Certificates.command` ফাইলটি রান করুন।

### ৩.৫.৩ Environment Variable সেটআপ করা (Alias তৈরি)

ইনস্টল করা টুলগুলো এখনো `PATH`-এ যোগ হয়নি। প্রতিবার ম্যানুয়ালি `export.sh` চালানোর বদলে একটা শর্টকাট (alias) তৈরি করা সুবিধাজনক।

আপনার shell profile ফাইলে (সাধারণত `~/.zshrc`, কারণ macOS Catalina-এর পর থেকে ডিফল্ট শেল zsh) নিচের লাইনটা যোগ করুন:

```bash
echo "alias get_idf='. \$HOME/esp/esp-idf/export.sh'" >> ~/.zshrc
source ~/.zshrc
```

এখন থেকে যেকোনো নতুন Terminal windows-এ শুধু `get_idf` লিখলেই ESP-IDF এনভায়রনমেন্ট অ্যাক্টিভেট হয়ে যাবে।

---

## ৩.৬ ধাপ ৪: New Project তৈরি এবং বিল্ড করা

Windows অধ্যায়ের মতোই, আমরা একটা Hello World প্রোগ্রাম তৈরি করে দেখব সবকিছু ঠিকঠাক কাজ করছে কিনা।

1. Desktop-এ **ESP-Programs** নামে একটি Folder তৈরি করুন (Finder দিয়ে, অথবা Terminal-এ `mkdir ~/Desktop/ESP-Programs`)।
2. VS Code-এ **File > Open Folder** থেকে এই ফোল্ডারটি ওপেন করুন।
3. এবার একটা নতুন Terminal window খুলুন (Spotlight থেকে) এবং ESP-IDF এনভায়রনমেন্ট অ্যাক্টিভেট করুন:

```bash
get_idf
```

*Figure: Activating ESP-IDF Environment*

সফল হলে **"Done! You can now compile ESP-IDF projects."** মেসেজ দেখতে পাবেন।

4. এবার প্রজেক্ট ফোল্ডারে প্রবেশ করুন এবং নতুন প্রজেক্ট তৈরি করুন:

```bash
cd ~/Desktop/ESP-Programs
idf.py create-project 01-Hello-World
```

5. এখন VS Code-এর Explorer-এ **01-Hello-World** নামে একটা নতুন ফোল্ডার দেখতে পাবেন। `main/01-Hello-World.c` ফাইলটি ওপেন করুন এবং নিচের কোডটি লিখুন:

```c
#include <stdio.h>

void app_main(void)
{
    printf("Hello World!\n");
}
```

6. Terminal-এ ফিরে গিয়ে প্রজেক্ট ফোল্ডারে প্রবেশ করুন এবং টার্গেট চিপ ও বিল্ড সেট করুন:

```bash
cd 01-Hello-World
idf.py set-target esp32
idf.py build
```

*Figure: Build Successful*

বিল্ড সফল হলে টার্মিনালে **"Project build complete."** মেসেজ দেখতে পাবেন।

---

## ৩.৭ ধাপ ৫: ESP32-তে প্রোগ্রাম আপলোড করা

1. USB ক্যাবল দিয়ে ESP32 Dev Kit V1 বোর্ডটি Mac-এর সাথে কানেক্ট করুন।

2. বোর্ডটি কোন সিরিয়াল ডিভাইস হিসেবে চিহ্নিত হয়েছে তা যাচাই করতে Terminal-এ চালান:

```bash
ls /dev/cu.*
```

আপনার USB-to-Serial চিপ অনুযায়ী একটা এন্ট্রি দেখতে পাবেন — যেমন `/dev/cu.usbserial-0001` (CP2102-এর জন্য) বা `/dev/cu.wchusbserial1420` (CH340-এর জন্য)।

*Figure: List Serial Devices*

> **নোট**: যদি কোনো ডিভাইস তালিকায় না আসে, তাহলে আপনার USB-to-Serial চিপের ড্রাইভার আলাদাভাবে ইনস্টল করতে হতে পারে — CP2102-এর জন্য Silicon Labs-এর ওয়েবসাইট থেকে **CP210x VCP Driver for macOS** ডাউনলোড করুন, অথবা CH340-এর জন্য WCH-এর ওয়েবসাইট থেকে macOS ড্রাইভার ডাউনলোড করুন। ইনস্টলের পর **System Settings > Privacy & Security**-এ গিয়ে ড্রাইভারটি Allow করতে হতে পারে।

3. এখন প্রজেক্টটি বিল্ড, ফ্ল্যাশ এবং সিরিয়াল মনিটর — একসাথে চালাতে নিচের কমান্ড ব্যবহার করুন (উপরে পাওয়া আপনার নিজের ডিভাইস পাথ বসিয়ে):

```bash
idf.py -p /dev/cu.usbserial-0001 flash monitor
```

*Figure: Flashing and Monitoring ESP32*

4. **Connecting...** মেসেজ দেখা গেলে সাথে সাথে বোর্ডের **Boot** বাটন চেপে ধরে রাখুন, এবং **Writing at 0x00010000...** মেসেজ দেখা গেলে বাটন ছেড়ে দিন।

5. ফ্ল্যাশ শেষ হলে Serial Monitor-এ **"Hello World!"** লেখা দেখতে পাবেন।

মনিটর থেকে বের হতে চাইলে `Ctrl + ]` চাপুন।

---

## ৩.৮ সাধারণ সমস্যা ও সমাধান

| সমস্যা | সম্ভাব্য কারণ ও সমাধান |
|---|---|
| `xcrun: error: invalid active developer path` | `xcode-select --install` আবার চালান |
| `command not found: brew` | Homebrew ইনস্টলেশনের পর টার্মিনাল রিস্টার্ট করুন, অথবা `PATH`-এ Homebrew যোগ করার কমান্ডটি (ইনস্টলেশনের শেষে দেখানো হয়) চালান |
| `bad CPU type in executable` (Apple Silicon) | Rosetta 2 ইনস্টল করুন: `/usr/sbin/softwareupdate --install-rosetta --agree-to-license` |
| `SSL: CERTIFICATE_VERIFY_FAILED` | Python ফোল্ডারে থাকা `Install Certificates.command` ফাইলটি রান করুন |
| `get_idf` কমান্ড কাজ করছে না | `~/.zshrc` ফাইলে alias ঠিকভাবে যোগ হয়েছে কিনা চেক করুন, তারপর `source ~/.zshrc` চালান |
| বোর্ড কানেক্ট করার পর `/dev/cu.*` এ কিছু দেখাচ্ছে না | USB ক্যাবল বদলে দেখুন (ডেটা ট্রান্সফার সাপোর্ট করে এমন কিনা); CP2102/CH340 ড্রাইভার ম্যানুয়ালি ইনস্টল করুন |

---

## ৩.৯ সারসংক্ষেপ

এই অধ্যায়ে আমরা করেছি:

- VS Code ইনস্টল করা
- Xcode Command Line Tools, Homebrew, এবং প্রয়োজনীয় বিল্ড টুল ইনস্টল করা
- Git দিয়ে ESP-IDF ডাউনলোড ও `install.sh` দিয়ে টুলচেইন সেটআপ করা
- `get_idf` alias দিয়ে সহজে ESP-IDF এনভায়রনমেন্ট অ্যাক্টিভেট করা
- Hello World প্রজেক্ট তৈরি, বিল্ড, ফ্ল্যাশ এবং মনিটর করা

Windows এবং macOS — দুই প্ল্যাটফর্মেই এখন আপনার এনভায়রনমেন্ট প্রস্তুত। সামনের একটি অধ্যায়ে আমরা VS Code-এর ভেতরেই পুরো ওয়ার্কফ্লোটা (Terminal, IntelliSense) আরও সহজ করে তোলার উপায় দেখব।

---

*[পরবর্তী অধ্যায়: ESP-এর জন্য VS Code কনফিগারেশন]*
