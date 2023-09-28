#include "cliutils.h"

int testCallback(Context *ctx, int argc, char *argv[]) {
    std::cout << "Hello Sir" << std::endl;
    return 0;
}

int main(int argc, char *argv[]) {
    CliApp app;
    app.name = "Tesst";
    app.shortDescription = "A test cli";
    app.version = "v1.0.0";
    app.description = "Warp is a powerful and versatile cross-platform download manager."
        "\nWith its advanced technology, Warp has the ability to accelerate"
        "\nyour download speeds by up to 10 times, revolutionizing the way"
        "\nyou obtain files on any operating system.";
    Command cmd;
    cmd.name = "test";
    cmd.shortDescription = "bleh bleh bleh";
    cmd.shorter = "t";
    cmd.description = "eany mefief ef f\nfefijf ef efjefijef efjijfej";
    cmd.callback = testCallback;
    app.setCommand(&cmd);
    Command cmd1;
    cmd1.name = "test2";
    cmd1.shortDescription = "bleh bleh bleh";
    cmd1.shorter = "t3";
    cmd1.description = "eany mefief ef f\nfefijf ef efjefijef efjijfej";
    cmd1.callback = testCallback;
    app.setCommand(&cmd1);
    Command cmd2;
    cmd2.name = "test1";
    cmd2.shortDescription = "bleh bleh bleh";
    cmd2.shorter = "t2";
    cmd2.description = "eany mefief ef f\nfefijf ef efjefijef efjijfej";
    cmd2.callback = testCallback;
    app.setCommand(&cmd2);
    return app.run(argc, argv);
}