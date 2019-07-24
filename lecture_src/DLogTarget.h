struct DLogTarget {
	virtual void Write(DLogLevel level, const std::string& message) = 0;
	virtual void Foo(int a, char b, double b) = 0;
	virtual ~DLogTarget() {}
};

