#include "app.h"

int writeCallback(Context *ctx, int argc, char *argv[]) {
    auto nameFlag =  static_cast<StringFlag*>(ctx->command->getFlag("p"));
    std::cout << "Path: "<< nameFlag->value << std::endl;
    std::cerr << "Error: This command has not been implemented yet!" << std::endl;
    return 1;
}


int main(int argc, char *argv[]) {
    CliApp app;
    app.name = "Coleon";
    app.shortDescription = "Coleon is a copyright header manager.";
    app.execName = "coleon";
    app.version = "v2.0.0";

    Command writeCmd;
    writeCmd.name = "write";
    writeCmd.shortDescription = "writes a copyright header to a file.";
    writeCmd.shorter = "w";
    writeCmd.callback = writeCallback;

    StringFlag pathFlag("./", "path to the file or directory");
    writeCmd.addFlag("p", &pathFlag);

    app.addCommand(&writeCmd);

    return app.run(argc, argv);
}