#pragma once
class FragmentShader
{
private:
	void initFragment();
public:
	FragmentShader();
	unsigned int getFragmentShader(int type);
	~FragmentShader();
};

