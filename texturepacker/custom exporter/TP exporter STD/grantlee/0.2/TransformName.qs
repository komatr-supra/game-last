var StripForbiddenSymbols = function(input)
{
    var str = input.rawString();
    str = str.replace(/[^a-zA-Z0-9]/g, "_");
    str = str.replace(/_+/g, "_");
    str = str.replace(/^_+|_+$/g, "");
    return "s_" + str;
};

var ChangeSpriteName = function(name)
{
    var spriteName = name.rawString();
    spriteName = spriteName.replace(/\//g, "_"); 
    return spriteName;
};

StripForbiddenSymbols.filterName = "stripForbiddenSymbols";
StripForbiddenSymbols.isSafe = true;
Library.addFilter("StripForbiddenSymbols"); 

ChangeSpriteName.filterName = "replaceBackslash";
ChangeSpriteName.isSafe = true;
Library.addFilter("ChangeSpriteName");
