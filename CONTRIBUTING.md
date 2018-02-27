## How to contribute to Camomile

First off, thanks for taking the time to contribute! This is a free and open-source project that couldn't exist without the contributions of everyone. There are several ways to contribute and you don't necessarily need to be a C/C++ programmer, a Pure Data guru or a master of the most popular digital audio workstations. Even if the fingers of a programmer are always welcome, the bug reports and the feature requests are essential to the development of the project. Indeed, it is impossible to predict the necessary features that will satisfy all the uses on all the digital audio workstations and it is impossible to verify their proper functioning on all the operating systems. Moreover, even a simple question is already a way of contributing because perhaps the answer could interest other people and bring new ideas but the most important is that you'll be able to help other people in return. Another good way to contribute is to improve the documentation, offer examples and create tutorials. At last, you can contribute directly to the code by submitting pull request.

#### How to ask a question, to submit a feature request or to report a bug

- First of all, **read the [documentation](https://github.com/pierreguillot/Camomile/wiki)**. You'll find answers to most of the questions you wanted to ask. It's pretty short and it mostly contains pictures. Taking few minutes to read it will save you a lot of time!

- Before asking a question, submitting a feature request or a bug report, **please ensure that somebody else has not already ask the same thing**. You can look for it in the [issues section](https://github.com/pierreguillot/Camomile/issues?utf8=%E2%9C%93&q=) of the Github repository.

- If you're unable to find an issue addressing the problem, [open a new one](https://github.com/pierreguillot/Camomile/issues/new). Be sure to include a **title and clear description**, as much relevant information as possible, and a patch to demonstrate your problem. It is also really important to specify your **operating system**, the **version of the plugin** that you use and the **digital audio workstation(s)** in which the problem occurs.

- If you found an issue that corresponds to your problem but this issue is closed, feel free to comment and/or reopen it and to **specify why it should be reopen**.

#### How to improve the documentation, to offer examples and to propose tutorials

- Contributing to the documentation can be done with git using the wiki repository: **https://github.com/pierreguillot/Camomile.wiki.git** or directly via the [wiki pages](https://github.com/pierreguillot/Camomile/wiki) by clicking on the button **edit** if you have Github account. The documentation probably contains typo errors and strange sentence formulations. In this case, feel free to change directly the master branch of the wiki and to describe the change. Some parts of the documentation is probably not clear enough or lacks of information. In this case, you can submit pull requests explaining what has changed and why and/or you can create a specific issue if you prefer to discuss it.

- A good place to offer examples and patches is on the website [patchstorage](https://patchstorage.com/platform/camomile/). The link to the platform Camomile is already in the [demos section](https://github.com/pierreguillot/Camomile/wiki/Demos-and-tutorials) of the documentation.

- In the [demos section](https://github.com/pierreguillot/Camomile/wiki/Demos-and-tutorials) of the documentation, you can also add your own links to websites, pages, tutorials, videos. But keep in mind that it must be related to Camomile. The goal is to help people, to demonstrate the funtionalities Camomile and to share patches. You can share links to your music and your personal work but you should also share your patches and/or explain how you did it.

#### How to help to the development of the plugin

- First of all, you should know that the master branch is used for the last stable release and the development branches are used for the next versions (for example **dev/v1.0.9**) and the new features (for example **dev/lv2-support**). The features branches are merged into the next versions' branches and the next versions' branches are merged into the master branch just before publishing a release.

- If you want to follow the current developments, the state of progressing of the next release or of a specific feature, you should refer to the [projects page](https://github.com/pierreguillot/Camomile/projects) of the Github repository.

- To compile the plugin, you should read the instructions on the [Compilation section](https://github.com/pierreguillot/Camomile/wiki/How-to-compile-the-plugins) of the documentation. These instruction should be valid for the master branch, it's possible that a development branch use a slightly different approach. In this case, you can should read the files used for the continuous integration (**.travis.yml** for Linux and MacOS and **appveyor.yml** for Windows) that are available in the git repository.


- Like for any other project, the best way to contribute is to submit pull requests. To avoid conflict, your branch should be mergeable into the branch of the next version. You can use [Appveyor](https://www.appveyor.com) and [Travis](travis-ci.org) to ensure your branch compiles well on Windows, MacOS and Linux.
