

set(dir src/)
add_subdirectory(actuators)
add_subdirectory(sensors)
add_subdirectory(workpiece)
add_subdirectory(productionStation)
add_subdirectory(gui)
set(src_files
        ${src_productionStation}
        ${src_actuators}
        ${src_sensors}
        ${src_gui}
        ${src_workpiece}
        ${dir}version.h
        ${dir}ObjMapper.cpp
        ${dir}ObjMapper.h
        ${dir}main.h
        PARENT_SCOPE )