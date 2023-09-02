set(ilbmthumnail_test_SRCS main.cpp ../ilbmcreator.cpp)
add_executable(test_ilbmthumbnail ${ilbmthumnail_test_SRCS})
target_link_libraries(test_ilbmthumbnail
    Qt5::Widgets
    KF5::KIOWidgets
    ${ImageMagick_Magick++_LIBRARY}
)

add_test(NAME scale_down
    COMMAND test_ilbmthumbnail ${CMAKE_CURRENT_SOURCE_DIR}/test.iff 128 128
)
add_test(NAME no_resize
    COMMAND test_ilbmthumbnail ${CMAKE_CURRENT_SOURCE_DIR}/test.iff 256 256
)
target_include_directories(test_ilbmthumbnail PUBLIC ${ImageMagick_Magick++_INCLUDE_DIRS})
