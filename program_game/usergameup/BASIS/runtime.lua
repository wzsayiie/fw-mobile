--LUA R"R(

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