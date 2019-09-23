--LUA R"R(

cid = {
    camera   = 1,
    code_beh = 2,
    xform    = 3,
}

function cid:from_cls(cls)

    if     cls:is_kind_of(camera  ) then return cid.camera
    elseif cls:is_kind_of(code_beh) then return cid.code_beh
    elseif cls:is_kind_of(xform   ) then return cid.xform
    
    else return 0
end

--)R"