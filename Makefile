
trainer: main.cpp command.hpp convert.hpp exec.hpp stream.hpp token.hpp types.hpp web.hpp command_base.hpp dict.hpp file.hpp text.hpp tokenization.hpp vocabulary.hpp
	$(CXX) -std=c++14 main.cpp -o trainer
