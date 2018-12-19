#ifndef _WRITER_
#define _WRITER_

class Writer {

public:

	void create_file();
	
	virtual ~Writer() {};
	
private:

	virtual void process() = 0;
	
};


#endif


