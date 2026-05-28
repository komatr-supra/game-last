var StripForbiddenSymbols = function(input)
{
  var input = input.rawString();
  
  // Nahradí vše, co NENÍ písmeno (a-z, A-Z) nebo číslo (0-9), za podtržítko
  input = input.replace(/[^a-zA-Z0-9]/g, "_");
  
  // Smrskne více podtržítek vedle sebe do jednoho
  input = input.replace(/_+/g, "_");
  
  // Odstraní případná podtržítka čistě na začátku a na konci řetězce
  input = input.replace(/^_+|_+$/g, "");
  
  // Přidá bezpečný prefix
  return "s_" + input;
};

StripForbiddenSymbols.filterName = "stripForbiddenSymbols";
StripForbiddenSymbols.isSafe = true;
Library.addFilter("StripForbiddenSymbols");
