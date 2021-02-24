/** 
 * @file Other.cpp
 * @brief Handles miscellaneous utility functions for RL-Bin in RLBinUtils class
 *
 * This source file contains implementaion of several utility functions which are
 * less frquently used for different purposes in RL-Bin.
 */

#include "../../include/SubUnits/Utils/defs.h"
#include "../../include/SubUnits/Utils/RLBinUtils.h"

using namespace std;

//Used for Capstone Compatibility
FILE _iob[] = { *stdin, *stdout, *stderr }; 
extern "C" FILE * __cdecl __iob_func(void)
{
    return _iob;
}

static std::string getCallConv(char code)
{
    static const std::map<char, std::string> callConvs
    {
        { 'A', "__cdecl   " },
        { 'I', "__fastcall" },
        { 'E', "__thiscall" },
        { 'G', "__stdcall " }
    };
    auto iter = callConvs.find(code);
    return (iter != std::end(callConvs)) ? iter->second : "";
}

static std::string getTypeName(char code)
{
    static const std::map<char, std::string> types
    {
        { 'C', "signed char   " },
        { 'D', "char          " },
        { 'E', "unsigned char " },
        { 'F', "short         " },
        { 'G', "unsigned short" },
        { 'H', "int           " },
        { 'I', "unsigned int  " },
        { 'J', "long          " },
        { 'K', "unsigned long " },
        { 'M', "float         " },
        { 'N', "double        " },
        { 'O', "long double   " },
        // These are just placeholders. A better demangler
        // would replace them with the actual type names.
        { 'P', "void*         " },
        { 'Q', "void[]        " },
        { 'U', "struct*       " },
        { 'V', "class*        " },
        { 'X', "void          " },
        { 'Z', "...           " }
    };
    auto iter = types.find(code);
    return (iter != std::end(types)) ? iter->second : "";
}

std::string demanglehelper(string mangledName, bool baseNameOnly)
{
    std::string demangledName;
    const char * ptr = mangledName.c_str();

    if (ptr == nullptr || *ptr == '\0')
    {
        return demangledName;
    }

    // MSFT C++ names always start with a question mark.
    if (*ptr != '?')
    {
        // Assume a C function with the default underscore prefix,
        // returning the original name minus the underscore. It might
        // also contain more name decoration at the end, so ignore
        // anything after the first '@' character.
        if (*ptr == '_')
        {
            for (++ptr; *ptr != '\0' && *ptr != '@'; ++ptr)
            {
                demangledName.push_back(*ptr);
            }
        }
        else
        {
            demangledName = ptr;
        }
        return demangledName + "()";
    }

    // Skip over the first '?'
    ++ptr;

    std::string funcName;
    std::string className;
    std::string callConv;
    std::string retType;

    // Now copy until an '@' or the end of the string to extract the function name:
    for (; *ptr != '\0' && *ptr != '@'; ++ptr)
    {
        funcName.push_back(*ptr);
    }

    // Same for the class name that follows if present:
    if (*ptr == '@')
    {
        for (++ptr; *ptr != '\0' && *ptr != '@'; ++ptr)
        {
            className.push_back(*ptr);
        }

        // Trailing '@'s after class name.
        for (; *ptr == '@' && *ptr != '\0'; ++ptr)
        {
        }
    }

    // Parameter list info is available but it's not being handled!
    if (!className.empty())
    {
        // A special member function: operators or constructor/destructor
        // (from a nested subclass... I'm no 100% sure if that's it, but looks like it...)
        if (funcName.length() >= 2 && funcName[0] == '?')
        {
            if (funcName[1] == '0') // Constructor
            {
                funcName = funcName.substr(2);
                demangledName = className + "::" + funcName + "::" + funcName + "()";
            }
            else if (funcName[1] == '1') // Destructor
            {
                funcName = funcName.substr(2);
                demangledName = className + "::" + funcName + "::~" + funcName + "()";
            }
            else if (funcName[1] == '4') // operator =
            {
                demangledName = className + "::" + funcName.substr(2) + "::operator=()";
            }
            else // The rest is currently ignored, but there's one for each num until 9 + A to Z.
            {
                std::size_t i;
                for (i = 0; i < funcName.length(); ++i)
                {
                    if (funcName[i] != '?' && funcName[i] != '_' && std::isalpha(funcName[i]))
                    {
                        break;
                    }
                }
                demangledName = className + "::" + funcName.substr(i) + "::???";
            }
        }
        else
        {
            // Apparently this is a template class...
            if (className.length() >= 2 && className[0] == '?' && className[1] == '$')
            {
                className = className.substr(2);
                className += "<T>";
            }
            if (!baseNameOnly) // Just the Class::Method() part?
            {
                // 'Q' should follow the '@' that separated a class name. Apparently meaningless.
                // 'S'/'2' I'm not sure... Does it mean a static class method???
                for (; *ptr != '\0' && (*ptr == 'Q' || *ptr == 'S' || *ptr == '2'); ++ptr)
                {
                }
                callConv += getCallConv(*ptr++);

                // The '_' is a qualifiers for "extended types", whatever that means.
                // It might precede the return type character.
                if (*ptr == '_')
                {
                    ++ptr;
                }
                retType += getTypeName(*ptr++);
                if (!callConv.empty())
                {
                    callConv += " ";
                }
                if (!retType.empty())
                {
                    retType += " ";
                }
            }
            demangledName = retType + callConv + className + "::" + funcName + "()";
        }
    }
    else
    {
        // A special member function: operators or constructor/destructor
        if (funcName.length() >= 2 && funcName[0] == '?')
        {
            if (funcName[1] == '0') // Constructor
            {
                funcName = funcName.substr(2);
                demangledName = funcName + "::" + funcName + "()";
            }
            else if (funcName[1] == '1') // Destructor
            {
                funcName = funcName.substr(2);
                demangledName = funcName + "::~" + funcName + "()";
            }
            else if (funcName[1] == '4') // operator =
            {
                demangledName = funcName.substr(2) + "::operator=()";
            }
            else // The rest is currently ignored, but there's one for each num until 9 + A to Z.
            {
                std::size_t i;
                for (i = 0; i < funcName.length(); ++i)
                {
                    if (funcName[i] != '?' && funcName[i] != '_' && std::isalpha(funcName[i]))
                    {
                        break;
                    }
                }
                demangledName = className + "::" + funcName.substr(i) + "::???";
            }
        }
        else
        {
            if (!baseNameOnly) // Just the Function() part?
            {
                // 'Y' should follow the '@'.
                // Probably just to differentiate from a class method...
                if (*ptr == 'Y')
                {
                    ++ptr;
                }
                callConv += getCallConv(*ptr++);

                if (*ptr == '_')
                {
                    ++ptr;
                }
                retType += getTypeName(*ptr++);

                if (!callConv.empty())
                {
                    callConv += " ";
                }
                if (!retType.empty())
                {
                    retType += " ";
                }
            }
            demangledName = retType + callConv + funcName + "()";
        }
    }
    return demangledName;
}

std::string RLBinUtils::demangle(std::string name)
{
    std::string myString = demanglehelper(name, true);
    return myString;
}

bool RLBinUtils::is_mangled(const char* name)
{
    string input_name(name);
    return (demangle(name) != input_name);
}