-- math_helpers.lua
function vector2(x, y)
    return {x = x, y = y}
end

function dotProduct(v1, v2)
    return v1.x * v2.x + v1.y * v2.y
end