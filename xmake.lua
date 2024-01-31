add_rules("mode.debug", "mode.release")

target("todolist")
    set_kind("binary")
    add_rules("qt.widgetapp")
    add_headerfiles("src/*.h")
    add_files("src/*.cpp")
    -- add files with Q_OBJECT meta (only for qt.moc)
    add_files("src/maintodolist.h")

    
    -- add_frameworks("QtWidgets")
    -- add_linkdirs("$(qt)/lib")