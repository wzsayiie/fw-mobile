--LUA R"R(

node = class("node", obj, {
})

function node:dont_destroy(obj)
    cs_dont_destroy_on_load(obj.native)
end

function node:destroy(obj)
    cs_destroy(obj.native)
end

--)R"