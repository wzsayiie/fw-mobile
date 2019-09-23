--LUA R"R(

gk_obj = class("gk_obj", obj, {
})

function gk_obj:dont_destroy(obj)
    cs_dont_destroy_on_load(obj.native)
end

function gk_obj:destroy(obj)
    cs_destroy(obj.native)
end

--)R"