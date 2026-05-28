var ExportJSON = function(tp) {
    var output = {
        textures: [], // full name of the generated atlases
        sprites: {}  // all sprites data
    };

    var t = tp.allResults[tp.variantIndex].textures;

    // all atlases (multipack support)
    for (var i = 0; i < t.length; i++) {
        var texture = t[i];
        output.textures.push(texture.fullName);

        // sprites in current atlas
        for (var j = 0; j < texture.allSprites.length; j++) {
            var sprite = texture.allSprites[j];
            // get rid of the "/" in sprite names -> replaced with "_"
            var name = sprite.trimmedName.replace(/\//g, "_");

            var isNSlice = sprite.scale9Enabled;

            // normalized pivot
            var ox = (sprite.pivotPoint.x - sprite.sourceRect.x) / sprite.sourceRect.width;
            var oy = (sprite.pivotPoint.y - sprite.sourceRect.y) / sprite.sourceRect.height;

            // sprite data
            output.sprites[name] = {
                atlas_id: i,
                x: sprite.frameRect.x,
                y: sprite.frameRect.y,
                w: sprite.frameRect.width,
                h: sprite.frameRect.height,
                ox: isNSlice ? 0 : Number(ox.toFixed(4)),
                oy: isNSlice ? 0 : Number(oy.toFixed(4))
            };

            // NSlice data for raylib's NPatchInfo
            // scale9Borders is a center rectangle!
            // NPatchInfo is a distance to edge!
            if (isNSlice) {
                output.sprites[name].slice = {
                    l: sprite.scale9Borders.x,
                    t: sprite.scale9Borders.y,
                    r: sprite.sourceRect.width - (sprite.scale9Borders.x + sprite.scale9Borders.width),
                    b: sprite.sourceRect.height - (sprite.scale9Borders.y + sprite.scale9Borders.height)
                };
            }
        }
    }

    return JSON.stringify(output, null, "\t");
};

// Register
ExportJSON.filterName = "exportJSON";
ExportJSON.isSafe = true; // no symbol changing
Library.addFilter("ExportJSON");