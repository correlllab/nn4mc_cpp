#include "Layer.h"

std::string Layer::type = std::string("abstract");
std::string Conv1D::type = std::string("conv1d");
std::string Conv2D::type = std::string("conv2d");
std::string Dense::type = std::string("dense");
std::string Flatten::type = std::string("flatten");
std::string MaxPooling1D::type = std::string("maxpool1d");
std::string MaxPooling2D::type = std::string("maxpool2d");
std::string SimpleRNN::type = std::string("simpleRNN");
std::string GRU::type = std::string("gru");
std::string LSTM::type = std::string("lstm");
std::string InputLayer::type = std::string("input");


// Define the available layer types -- NOTE:  NOT ACTUALLY USING THIS!!!
std::array<std::string, 9> Layer::layer_types = { 	std::string("conv1d"),
													std::string("conv2d"),
													std::string("dense"),
													std::string("flatten"),
													std::string("maxpool1d"),
													std::string("maxpool2d"),
													std::string("simpleRNN"),
													std::string("gru"),
													std::string("lstm")
												};

Layer::Layer(std::string id)
{
	identifier = id;
}


Conv1D::Conv1D(std::string id) : Layer(id)
{
	layer_type = Conv1D::type;
}

Conv2D::Conv2D(std::string id) : Layer(id)
{
	layer_type = Conv2D::type;
}

Dense::Dense(std::string id) : Layer(id)
{
	layer_type = Dense::type;
}

Flatten::Flatten(std::string id) : Layer(id)
{
	layer_type = Flatten::type;
}

MaxPooling1D::MaxPooling1D(std::string id) : Layer(id)
{
	layer_type = MaxPooling1D::type;
}

MaxPooling2D::MaxPooling2D(std::string id) : Layer(id)
{
	layer_type = MaxPooling2D::type;
}

SimpleRNN::SimpleRNN(std::string id) : Layer(id)
{
	layer_type = SimpleRNN::type;
}

GRU::GRU(std::string id) : Layer(id)
{
	layer_type = GRU::type;
}

LSTM::LSTM(std::string id) : Layer(id)
{
	layer_type = LSTM::type;
}

InputLayer::InputLayer(std::string id) : Layer(id)
{
	layer_type = InputLayer::type;
}
