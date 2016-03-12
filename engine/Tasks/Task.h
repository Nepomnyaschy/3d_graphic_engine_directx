#pragma once


class Task
{
public:
	virtual ~Task() { }

	virtual void Init()		{ }
	virtual void Update()	{ }
};