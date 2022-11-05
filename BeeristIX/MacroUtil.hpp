#pragma once

// CCC - CommandClassCreator
#define CCC(x) std::make_unique<Beerist::Commands::x>()

// CM - CommandMaker
#define CM(x) Beerist::Commands::x::returnData(debugGuild, args->getBotUser().id)

// CR - CommandRegister
#define CR(z, x, y) commands.emplace_back(CM(x)); args->registerFunction(std::vector<std::string>{ z }, CCC(x), commands[y])