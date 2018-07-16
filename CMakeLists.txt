cmake_minimum_required(VERSION "3.0")

project(wallgen C)

function(make_gen name)
	add_executable(${name} "src/${name}.c")
	target_link_libraries(${name} m)
endfunction()

make_gen(w0_colorcircle)
make_gen(w1_stripes)
make_gen(w2_blocks)

configure_file(extra/make_samples.sh ${CMAKE_CURRENT_BINARY_DIR})
configure_file(extra/fehview.sh ${CMAKE_CURRENT_BINARY_DIR})
