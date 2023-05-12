//
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Author:  David Elder
//

#pragma once

#include "Application.h"

#include <iostream>

class A
{
public:
	A()
	{
		std::cout << "A ctor" << std::endl;
	}
	~A()
	{
		std::cout << "A dtor" << std::endl;
	}
};


class B
{
public:
	B()
	{
		std::cout << "B ctor" << std::endl;
	}
	~B()
	{
		std::cout << "B dtor" << std::endl;
	}
};


class C
{
public:
	C()
	{
		std::cout << "C ctor" << std::endl;
	}
	~C()
	{
		std::cout << "C dtor" << std::endl;
	}
};


class TestApp : public Kodiak::Application
{
public:
	explicit TestApp(const Kodiak::ApplicationDesc& desc) 
		: Application(desc)
	{}

	void Configure() final;
	void Startup() final;
	void Shutdown() final;

	bool Update() final;
	void Render() final;

private:
	// Add member functions here

private:
	// Add data members here
};