#include "cliutils.h"

int testCallbacl(Context *ctx, int argc, char *argv[]) {
    std::cout << "Hello Sir" << std::endl;
    return 0;
}

int main(int argc, char *argv[]) {
    CliApp app;
    app.enableVerbose();
    app.name = "Test";
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
    app.setCommand(&cmd);
    return app.run(argc, argv);
}