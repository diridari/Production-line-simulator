set(dir src/)
add_subdirectory(actuators)
add_subdirectory(sensors)
add_subdirectory(workpiece)
add_subdirectory(productionStation)
add_subdirectory(gui)
add_subdirectory(api)
set(src_files
        ${src_productionStation}
        ${src_actuators}
        ${src_sensors}
        ${src_workpiece}
        ${src_api}
        ${dir}version.h

        ${dir}main.h
        PARENT_SCOPE )

set(src_gui
        ${src_gui}
        PARENT_SCOPE )
