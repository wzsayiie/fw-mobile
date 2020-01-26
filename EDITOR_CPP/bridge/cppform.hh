//==== ==== ==== ==== ==== header ==== ==== ==== ==== ====
static const char *intf_header = R"OO(

//$header.
//this file generated by automation tool, don't modify it manually.

#include "cqbridgeobject.hh"

$loop_class
cq_declare($cppcls);
$end

$need
$loop_class
$loop_static
$ret _cpp_$(class)_$func($params);
$end
$end

$loop_class
cq_class($cppcls, cqBridgeObject) {

$loop_static
    static $ret $func($params);
$end
$loop_virtual
    virtual $ret $func($params) = 0;
$end
};

$end
)OO";

//==== ==== ==== ==== ==== interface source ==== ==== ==== ==== ====
static const char *intf_source = R"OO(

)OO";

//==== ==== ==== ==== ==== implementation source ==== ==== ==== ==== ====
static const char *impl_source = R"OO(

)OO";