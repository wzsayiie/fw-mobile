--LUA R"R(

package.path = package.path .. ";program_game/usergameup/BASIS/?.lua"
package.path = package.path .. ";program_game/usergameup/foundation/?.lua"
package.path = package.path .. ";program_game/usergameup/gamekit/?.lua"
package.path = package.path .. ";program_game/usergameup/subsystem/?.lua"
package.path = package.path .. ";program_game/usergameup/usergame/?.lua"

-- require:
setmetatable(_G, {__index = function(tab, key)
    if pcall(require, string.lower(key)) then
        return tab[key]
    else
        return nil
    end
end})

-- app entry:
entry()

--)R"