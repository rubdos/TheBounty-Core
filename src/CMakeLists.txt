add_subdirectory(yafraycore)
add_subdirectory(backgrounds)
add_subdirectory(cameras)
add_subdirectory(image_handlers)
add_subdirectory(integrators)
add_subdirectory(interface)
add_subdirectory(lights)
add_subdirectory(materials)
add_subdirectory(textures)
add_subdirectory(volumes)

if(WITH_XML_LOADER)
	add_subdirectory(xml_loader)
endif(WITH_XML_LOADER)

if(WITH_QT)
	add_subdirectory(gui)
endif(WITH_QT)

add_subdirectory(bindings)
