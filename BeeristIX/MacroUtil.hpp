#pragma once

// CCC - CommandClassCreator
#define CCC(x) std::make_unique<Beerist::Commands::x>()

// CR - CommandRegister
#define CR(z, x, y) args->registerFunction(std::vector<std::string>{ z }, CCC(x), commands[y])

// CM - CommandMaker
#define CM(x) Beerist::Commands::x::returnData(debug_guild, args->getBotUser().id)