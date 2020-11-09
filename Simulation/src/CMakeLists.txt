

set(dir src/)
add_subdirectory(actuators)
add_subdirectory(sensors)
add_subdirectory(workpiece)
add_subdirectory(productionStation)
set(src_files
        ${src_productionStation}
        ${src_actuators}
        ${src_sensors}
        ${src_workpiece}
        ${dir}version.h
        PARENT_SCOPE )