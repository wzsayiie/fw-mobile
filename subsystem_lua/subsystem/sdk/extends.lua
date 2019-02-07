function extends(super, this)
    setmetatable(this, {__index = super})
    this.super = super
    return this
end
