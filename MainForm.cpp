#include "MainForm.h"
#include "htmlParser.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace parser;

[STAThreadAttribute]
int main(array<String^>^ args)
{
	ParserHTML parser;
	parser.findSpansByClass();

	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	Cursach::MainForm form;
	Application::Run(%form);
}
