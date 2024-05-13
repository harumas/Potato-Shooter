#include "ResourceHandler.h"


int* ResourceHandler::load_div_graph(const string file_name, int count, int x_num, int y_num, int x_size, int y_size)
{
	int* handle_array = (int*)malloc(sizeof(int) * count);
	LoadDivGraph((rootPath + file_name).c_str(), count, x_num, y_num, x_size, y_size, handle_array);

	return handle_array;
}

int ResourceHandler::load_graph(const string path_data)
{
	//キャッシュに指定のファイルが存在した場合はそれを返す 
	auto cache = graph_handle_cache.find(path_data);
	if (cache != graph_handle_cache.end())
	{
		return cache->second;
	}

	string ext = string(strrchr(path_data.c_str(), '.'));

	// 画像リソースのロード
	for (string s_ext : support_graph)
	{
		if (ext != s_ext) continue;

		int handle = LoadGraph((rootPath + path_data).c_str());
		graph_handle_cache[path_data] = handle; //キャッシュする

		return handle;
	}

	return -1;
}

int ResourceHandler::load_audio(const string path_data)
{
	//キャッシュに指定のファイルが存在した場合はそれを返す 
	auto cache = audio_handle_cache.find(path_data);
	if (cache != audio_handle_cache.end())
	{
		return cache->second;
	}

	string ext = string(strrchr(path_data.c_str(), '.'));

	// 音声リソースのロード
	for (string s_ext : support_audio)
	{
		if (ext != s_ext) continue;

		int handle = LoadSoundMem((rootPath + path_data).c_str());
		audio_handle_cache[path_data] = handle; //キャッシュする

		return handle;
	}

	return -1;
}

void ResourceHandler::draw_graph(int x, int y, int handle, bool scaleToScreen)
{
	if (scaleToScreen)
	{ // 縦画面に合わせてスケール
		int graph_w, graph_h;
		GetGraphSize(handle, &graph_w, &graph_h);
		int aspect = graph_w / graph_h;

		DrawExtendGraph(x, y, App::screen_w * aspect + x + 1, App::screen_h + y + 1, handle, TRUE);
	}
	else
	{
		DrawGraph(x, y, handle, TRUE);
	}
}

void ResourceHandler::draw_extend_graph(int x, int y, double ext_rate, int handle)
{
	int graph_w, graph_h;

	GetGraphSize(handle, &graph_w, &graph_h);

	graph_w = (int)(graph_w * ext_rate / 2.0);
	graph_h = (int)(graph_h * ext_rate / 2.0);

	DrawExtendGraph(x - graph_w, y - graph_h, x + graph_w, y + graph_h, handle, TRUE);
}
void ResourceHandler::draw_rota_graph(int x, int y, int rot_offset, double angle, int handle, double ext_rate, bool is_turn)
{
	double rad = deg_to_rad(angle);

	int dx = (int)(-sin(rad) * rot_offset);
	int dy = (int)(cos(rad) * rot_offset);

	DrawRotaGraph(x + dx, y + dy, ext_rate, rad, handle, TRUE, is_turn);
}

ResourceHandler::~ResourceHandler()
{}


