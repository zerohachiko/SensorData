set(FOO_SRCS
	main.cpp
	DataTxt.h
	DataTxt.cpp
	HttpPost.h
	HttpPost.cpp
	HMAC_SHA1.cpp
	HMAC_SHA1.h
	SHA1.cpp
	SHA1.h


)

QT4_WRAP_CPP(FOO_MOC_H HttpPost.h DataTxt.h)

#QT4_WRAP_UI(FOO_UIS_H ${FOO_UIS})

ADD_EXECUTABLE(SensorData 
		${FOO_SRCS} 
		${FOO_MOC_H} 
)
		

TARGET_LINK_LIBRARIES(SensorData ${QT_LIBRARIES})
SET_TARGET_PROPERTIES(SensorData PROPERTIES FOLDER "Apps")
INSTALL_TARGETS(/bin SensorData)
