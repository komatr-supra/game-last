var StripForbiddenSymbols = function(input)
{
  var input = input.rawString();
  input = input.replace(/[^a-zA-Z0-9]/g, "_");
  input = input.replace(/_+/g, "_");
  input = input.replace(/^_+|_+$/g, "");
  return "s_" + input;
};

var ChangeSpriteName = function(name)
{
  var spriteName = name.rawString();
  spriteName.replace(/\//g, "_");
  return spriteName;
}

StripForbiddenSymbols.filterName = "stripForbiddenSymbols";
StripForbiddenSymbols.isSafe = true;
Library.addFilter("StripForbiddenSymbols");

ChangeSpriteName.filterName = "replaceBackslash";
ChangeSpriteName.isSafe = true;
Library.addFilter("ChangeSpriteName");
