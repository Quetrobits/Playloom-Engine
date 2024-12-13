-- player_behavior.lua
function updatePlayerPosition(player, deltaTime)
    local speed = 5
    player.x = player.x + speed * deltaTime
    -- Add logic for player input or AI-controlled movement
end