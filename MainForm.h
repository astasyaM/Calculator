#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <msclr/marshal_cppstd.h>
#include <cctype>
#include <vector>
#include <stdexcept>
#include <map>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cfenv>
#include <fenv.h>
#include <thread>
#include <mutex>
#include <future>
#include <functional>
#include <windows.h>
#include "..\akios_project\ProjectLib\ProjectLib\Header.h"
 

namespace akiosproject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading::Tasks;
	using namespace System::Threading;

	//переменные, в которых будут храниться результаты вычислений для последующего вывода в форму
	double result1, result2;

	//структура для построения дерева для вычислений
	struct Node {
		std::string data;
		Node* left;
		Node* right;
		Node(const std::string& data) : data(data), left(nullptr), right(nullptr) {}
	};

	std::mutex fileMutex; //мьютекс для безопасного доступа к файлу
	std::string selectedFilePath = "formulas.txt"; //название файла, с которым в данный момент работает пользователь

	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ LblEnter;
	protected:

	private: System::Windows::Forms::TextBox^ FormulaEntering;

	private: System::Windows::Forms::Label^ LblChoose;

	private: System::Windows::Forms::DomainUpDown^ ChooseFormula;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::Windows::Forms::Label^ LblHistory;

	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::ListBox^ HistoryList;

	private: System::Windows::Forms::VScrollBar^ vScrollBar1;
	private: System::Windows::Forms::Label^ LblMeaning;

	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
	private: System::Windows::Forms::Button^ BtnOpenFile;
	private: System::Windows::Forms::Button^ BtnNewFile;
	private: System::Windows::Forms::Button^ button1;

	private: System::Windows::Forms::Button^ BtnCount;
	private: System::Windows::Forms::Label^ LblEnter2;

	private: System::Windows::Forms::TextBox^ FormulaEntering2;

	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ LblChoose2;

	private: System::Windows::Forms::DomainUpDown^ ChooseFormula2;
	private: System::Windows::Forms::Label^ LblMeaning2;

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->LblEnter = (gcnew System::Windows::Forms::Label());
			this->FormulaEntering = (gcnew System::Windows::Forms::TextBox());
			this->LblChoose = (gcnew System::Windows::Forms::Label());
			this->ChooseFormula = (gcnew System::Windows::Forms::DomainUpDown());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->LblHistory = (gcnew System::Windows::Forms::Label());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->HistoryList = (gcnew System::Windows::Forms::ListBox());
			this->vScrollBar1 = (gcnew System::Windows::Forms::VScrollBar());
			this->LblMeaning = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->BtnNewFile = (gcnew System::Windows::Forms::Button());
			this->BtnOpenFile = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->BtnCount = (gcnew System::Windows::Forms::Button());
			this->LblEnter2 = (gcnew System::Windows::Forms::Label());
			this->FormulaEntering2 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->LblChoose2 = (gcnew System::Windows::Forms::Label());
			this->ChooseFormula2 = (gcnew System::Windows::Forms::DomainUpDown());
			this->LblMeaning2 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// LblEnter
			// 
			this->LblEnter->AutoSize = true;
			this->LblEnter->Location = System::Drawing::Point(13, 10);
			this->LblEnter->Name = L"LblEnter";
			this->LblEnter->Size = System::Drawing::Size(82, 13);
			this->LblEnter->TabIndex = 0;
			this->LblEnter->Text = L"Ввод формулы";
			// 
			// FormulaEntering
			// 
			this->FormulaEntering->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->FormulaEntering->Location = System::Drawing::Point(12, 26);
			this->FormulaEntering->Name = L"FormulaEntering";
			this->FormulaEntering->Size = System::Drawing::Size(263, 20);
			this->FormulaEntering->TabIndex = 1;
			// 
			// LblChoose
			// 
			this->LblChoose->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->LblChoose->AutoSize = true;
			this->LblChoose->Location = System::Drawing::Point(13, 76);
			this->LblChoose->Name = L"LblChoose";
			this->LblChoose->Size = System::Drawing::Size(90, 13);
			this->LblChoose->TabIndex = 3;
			this->LblChoose->Text = L"Выбор формулы";
			// 
			// ChooseFormula
			// 
			this->ChooseFormula->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->ChooseFormula->Location = System::Drawing::Point(12, 93);
			this->ChooseFormula->Name = L"ChooseFormula";
			this->ChooseFormula->Size = System::Drawing::Size(263, 20);
			this->ChooseFormula->TabIndex = 4;
			this->ChooseFormula->SelectedItemChanged += gcnew System::EventHandler(this, &MainForm::ChooseFormula_SelectedItemChanged);
			// 
			// LblHistory
			// 
			this->LblHistory->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->LblHistory->AutoSize = true;
			this->LblHistory->Location = System::Drawing::Point(336, 10);
			this->LblHistory->Name = L"LblHistory";
			this->LblHistory->Size = System::Drawing::Size(114, 13);
			this->LblHistory->TabIndex = 5;
			this->LblHistory->Text = L"История вычислений";
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// HistoryList
			// 
			this->HistoryList->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->HistoryList->FormattingEnabled = true;
			this->HistoryList->Location = System::Drawing::Point(281, 26);
			this->HistoryList->Name = L"HistoryList";
			this->HistoryList->Size = System::Drawing::Size(223, 290);
			this->HistoryList->TabIndex = 6;
			// 
			// vScrollBar1
			// 
			this->vScrollBar1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->vScrollBar1->Location = System::Drawing::Point(487, 26);
			this->vScrollBar1->Name = L"vScrollBar1";
			this->vScrollBar1->Size = System::Drawing::Size(17, 294);
			this->vScrollBar1->TabIndex = 7;
			this->vScrollBar1->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &MainForm::vScrollBar1_Scroll);
			// 
			// LblMeaning
			// 
			this->LblMeaning->AutoSize = true;
			this->LblMeaning->Location = System::Drawing::Point(9, 125);
			this->LblMeaning->Name = L"LblMeaning";
			this->LblMeaning->Size = System::Drawing::Size(120, 13);
			this->LblMeaning->TabIndex = 8;
			this->LblMeaning->Text = L"Значение переменной";
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 2;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel2->Controls->Add(this->BtnNewFile, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->BtnOpenFile, 0, 0);
			this->tableLayoutPanel2->Location = System::Drawing::Point(281, 323);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 1;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(223, 37);
			this->tableLayoutPanel2->TabIndex = 11;
			// 
			// BtnNewFile
			// 
			this->BtnNewFile->Location = System::Drawing::Point(114, 3);
			this->BtnNewFile->Name = L"BtnNewFile";
			this->BtnNewFile->Size = System::Drawing::Size(106, 31);
			this->BtnNewFile->TabIndex = 1;
			this->BtnNewFile->Text = L"Новый файл";
			this->BtnNewFile->UseVisualStyleBackColor = true;
			this->BtnNewFile->Click += gcnew System::EventHandler(this, &MainForm::BtnNewFile_Click);
			// 
			// BtnOpenFile
			// 
			this->BtnOpenFile->Location = System::Drawing::Point(3, 3);
			this->BtnOpenFile->Name = L"BtnOpenFile";
			this->BtnOpenFile->Size = System::Drawing::Size(105, 31);
			this->BtnOpenFile->TabIndex = 0;
			this->BtnOpenFile->Text = L"Открыть файл";
			this->BtnOpenFile->UseVisualStyleBackColor = true;
			this->BtnOpenFile->Click += gcnew System::EventHandler(this, &MainForm::BtnOpenFile_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 47);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(83, 26);
			this->button1->TabIndex = 12;
			this->button1->Text = L"Применить";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// BtnCount
			// 
			this->BtnCount->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->BtnCount->Location = System::Drawing::Point(281, 366);
			this->BtnCount->Name = L"BtnCount";
			this->BtnCount->Size = System::Drawing::Size(223, 41);
			this->BtnCount->TabIndex = 0;
			this->BtnCount->Text = L"Рассчитать";
			this->BtnCount->UseVisualStyleBackColor = true;
			this->BtnCount->Click += gcnew System::EventHandler(this, &MainForm::BtnCount_Click);
			// 
			// LblEnter2
			// 
			this->LblEnter2->AutoSize = true;
			this->LblEnter2->Location = System::Drawing::Point(694, 10);
			this->LblEnter2->Name = L"LblEnter2";
			this->LblEnter2->Size = System::Drawing::Size(82, 13);
			this->LblEnter2->TabIndex = 14;
			this->LblEnter2->Text = L"Ввод формулы";
			// 
			// FormulaEntering2
			// 
			this->FormulaEntering2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->FormulaEntering2->Location = System::Drawing::Point(513, 26);
			this->FormulaEntering2->Name = L"FormulaEntering2";
			this->FormulaEntering2->Size = System::Drawing::Size(263, 20);
			this->FormulaEntering2->TabIndex = 15;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(693, 47);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(83, 26);
			this->button2->TabIndex = 16;
			this->button2->Text = L"Применить";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
			// 
			// LblChoose2
			// 
			this->LblChoose2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->LblChoose2->AutoSize = true;
			this->LblChoose2->Location = System::Drawing::Point(686, 76);
			this->LblChoose2->Name = L"LblChoose2";
			this->LblChoose2->Size = System::Drawing::Size(90, 13);
			this->LblChoose2->TabIndex = 17;
			this->LblChoose2->Text = L"Выбор формулы";
			// 
			// ChooseFormula2
			// 
			this->ChooseFormula2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->ChooseFormula2->Location = System::Drawing::Point(513, 93);
			this->ChooseFormula2->Name = L"ChooseFormula2";
			this->ChooseFormula2->Size = System::Drawing::Size(263, 20);
			this->ChooseFormula2->TabIndex = 18;
			this->ChooseFormula2->SelectedItemChanged += gcnew System::EventHandler(this, &MainForm::ChooseFormula2_SelectedItemChanged);
			// 
			// LblMeaning2
			// 
			this->LblMeaning2->AutoSize = true;
			this->LblMeaning2->Location = System::Drawing::Point(656, 125);
			this->LblMeaning2->Name = L"LblMeaning2";
			this->LblMeaning2->Size = System::Drawing::Size(120, 13);
			this->LblMeaning2->TabIndex = 19;
			this->LblMeaning2->Text = L"Значение переменной";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(788, 419);
			this->Controls->Add(this->LblMeaning2);
			this->Controls->Add(this->ChooseFormula2);
			this->Controls->Add(this->LblChoose2);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->FormulaEntering2);
			this->Controls->Add(this->LblEnter2);
			this->Controls->Add(this->BtnCount);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->tableLayoutPanel2);
			this->Controls->Add(this->LblMeaning);
			this->Controls->Add(this->vScrollBar1);
			this->Controls->Add(this->HistoryList);
			this->Controls->Add(this->LblHistory);
			this->Controls->Add(this->ChooseFormula);
			this->Controls->Add(this->LblChoose);
			this->Controls->Add(this->FormulaEntering);
			this->Controls->Add(this->LblEnter);
			this->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->MaximumSize = System::Drawing::Size(804, 458);
			this->MinimumSize = System::Drawing::Size(566, 411);
			this->Name = L"MainForm";
			this->Text = L" Калькулятор";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->tableLayoutPanel2->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
/// <summary>
/// Метод для стартового вида формы - загружает данные из файла "formulas.txt" в историю операций и окна выбора формул
/// </summary>
/// <param name="sender">Объект-инициатор события</param>
/// <param name="e">Аргументы события</param>
private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	System::IO::StreamReader^ file;

	try {
		file = gcnew System::IO::StreamReader("formulas.txt"); // Пытаемся открыть файл для чтения
	}
	catch (System::IO::FileNotFoundException^) {
		file = gcnew System::IO::StreamReader("formulas.txt", true); // Если файл отсутствует, создаем новый
	}

	// Чтение файла и добавление строк в ListBox, отфильтровывая НЕ формулы
	while (!file->EndOfStream) {
		System::String^ line = file->ReadLine(); // Чтение строки из файла
		HistoryList->Items->Add(line); // Добавление строки в список истории операций

		// Проверка строки на соответствие формуле и добавление в список формул для обоих потоков
		if (isValidExpressionForAdd(msclr::interop::marshal_as<std::string>(line)) && line->Length > 1) {
			ChooseFormula->Items->Add(line); // Добавление в список формул первого потока
			ChooseFormula2->Items->Add(line); // Добавление в список формул второго потока
		}
	}

	file->Close(); // Закрытие файла после чтения данных
	Wellcome();
}

	private:
		
		/// <summary>
		/// является ли символ открывающей скобкой
		/// </summary>
		/// <param name="c">символ</param>
		/// <returns>true если это открывающая скобка, false в противном случае</returns>
		bool isOpeningBracket(char c) {
			return c == '(';
		}

		/// <summary>
		/// является ли символ закрывающей скобкой
		/// </summary>
		/// <param name="c">символ</param>
		/// <returns>true если это закрывающая скобка, false в противном случае</returns>
		bool isClosingBracket(char c) {
			return c == ')';
		}

		/// <summary>
		/// Является ли символ оператором
		/// </summary>
		/// <param name="c">символ</param>
		/// <returns>true если является, false в противном случае</returns>
		bool isOperator(char c) {
			return (c == '+' || c == '-' || c == '*' || c == '/');
		}

		/// <summary>
		/// Является ли символ частью дробного числа
		/// </summary>
		/// <param name="c">символ</param>
		/// <returns>true если является, false в противном случае</returns>
		bool isNumericChar(char c) {
			return (isdigit(c) || c == '.' || c == '-');
		}

		/// <summary>
		/// Является ли символ операндом
		/// </summary>
		/// <param name="c">символ</param>
		/// <returns>true если операнд, false в противном случае</returns>
		bool isOperand(char c) {
			return std::isdigit(c) || std::isalpha(c);
		}

		/// <summary>
		/// Проверка, является ли введённая формула корректной (без сообщений, для считывания из файла)
		/// </summary>
		/// <param name="expression">Введённое выражение</param>
		/// <returns>true если выражение корректно, false если не корректно</returns>
		bool isValidExpressionForAdd(const std::string& expression) {
			std::stack<char> brackets; // Стек для отслеживания скобок
			char previousChar = '\0'; // Переменная для хранения предыдущего символа

			for (size_t i = 0; i < expression.length(); ++i) {
				// Проверка текущего символа

				if (isOpeningBracket(expression[i])) { // Если это открывающая скобка
					brackets.push(expression[i]); // Помещаем в стек

				}
				else if (isClosingBracket(expression[i])) { // Если это закрывающая скобка
					if (brackets.empty() || !isOpeningBracket(brackets.top())) { // Проверяем, что есть соответствующая открывающая скобка
						return false; // Если нет, выражение не корректно
					}
					brackets.pop(); // Иначе удаляем соответствующую открывающую скобку из стека

				}
				else if (isOperator(expression[i])) { // Если это оператор
					if (i == 0 || i == expression.length() - 1) { // Проверяем, что оператор не находится в начале или в конце выражения
						return false;
					}
					if (isOperator(previousChar)) { // Проверяем, что предыдущий символ не является оператором
						return false;
					}

				}
				else if (isOperand(expression[i])) { // Если это операнд
					if (isOperand(previousChar)) { // Проверяем, что предыдущий символ не является операндом
						return false;
					}

				}
				else {
					return false; // Если символ не является ни скобкой, ни оператором, ни операндом, выражение не корректно
				}

				previousChar = expression[i]; // Обновляем предыдущий символ
			}

			if (!brackets.empty()) { // Проверяем, остались ли открытые скобки
				return false;
			}

			return true; // Возвращаем true, если все условия проверки выполнены успешно
		}

		/// <summary>
		/// Проверка, является ли введённая формула корректной (с сообщениями)
		/// </summary>
		/// <param name="expression">Введённое выражение</param>
		/// <returns>true, если выражение корректно; false, если некорректно</returns>
		bool isValidExpression(const std::string& expression) {
			std::stack<Node*> nodeStack; // Стек для хранения узлов дерева выражения
			std::stack<char> opStack;    // Стек для хранения операторов (+, -, *, /)
			std::string operand;         // Строка для сбора операндов (чисел) из выражения

			for (size_t i = 0; i < expression.size(); ++i) {
				char c = expression[i];

				if (isspace(c)) { // Пропускаем пробелы
					continue;
				}
				else if (isdigit(c) || c == '.') { // Если символ - цифра или точка, добавляем к операнду
					if (isdigit(c))
						operand += c;

				}
				else { // Если символ - оператор или скобка
					if (!operand.empty()) { // Если был собран операнд, добавляем его в стек узлов
						nodeStack.push(createOperandNode(std::stod(operand)));
						operand.clear();
					}

					if (c == '(') {
						opStack.push(c); // Если символ - открывающая скобка, добавляем её в стек операторов
					}
					else if (c == ')') { // Если символ - закрывающая скобка
						while (!opStack.empty() && opStack.top() != '(') {
							char op = opStack.top();
							opStack.pop();

							if (nodeStack.size() < 2) {
								return false; // Если операндов недостаточно для операции, выражение некорректно
							}

							Node* right = nodeStack.top();
							nodeStack.pop();
							Node* left = nodeStack.top();
							nodeStack.pop();

							nodeStack.push(createOperatorNode(std::string(1, op), left, right)); // Создаем узел операции и добавляем в стек узлов
						}
						if (!opStack.empty()) {
							opStack.pop(); // Удаляем открывающую скобку из стека операторов
						}
						else {
							return false; // Нет соответствующей открывающей скобки, выражение некорректно
						}
					}
					else if (c == '+' || c == '-' || c == '*' || c == '/') { // Если символ - оператор
						while (!opStack.empty() && opStack.top() != '(' && getPriority(opStack.top()) >= getPriority(c)) {
							char op = opStack.top();
							opStack.pop();

							if (nodeStack.size() < 2) {
								return false; // Если операндов недостаточно для операции, выражение некорректно
							}

							Node* right = nodeStack.top();
							nodeStack.pop();
							Node* left = nodeStack.top();
							nodeStack.pop();

							nodeStack.push(createOperatorNode(std::string(1, op), left, right)); // Создаем узел операции и добавляем в стек узлов
						}
						opStack.push(c); // Добавляем текущий оператор в стек операторов
					}
					else {
						return true; // Любой другой символ считается некорректным в выражении
					}
				}
			}
		}


private: System::Void vScrollBar1_Scroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e) {
	//привязываем скроллбар к полю с историей вычислений
	HistoryList->TopIndex = vScrollBar1->Value;
}
	   /// <summary>
       /// Получение имён переменных, для которых нужно получить значения, из формулы.
       /// </summary>
       /// <param name="formula">Строка формулы</param>
       /// <returns>Вектор идентификаторов переменных</returns>
	   std::vector<std::string> GetVariablesFromFormula(const std::string& formula) {
		   std::vector<std::string> variables;

		   //проход по строке формулы
		   size_t i = 0;
		   while (i < formula.length()) {
			   std::string variable;

			   //пропуск пробелов и символов операций
			   while (i < formula.length() && (std::isspace(formula[i]) || formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/' || formula[i] == '(' || formula[i] == ')' || isdigit(formula[i]))) {
				   i++;
			   }

			   //формирование идентификатора переменной
			   while (i < formula.length() && (std::isalpha(formula[i]) || std::isdigit(formula[i]))) {
				   variable += formula[i];
				   i++;
			   }

			   //добавление переменной в список, если она не пустая
			   if (!variable.empty()) {
				   variables.push_back(variable);
			   }
		   }

		   return variables;
	   }


	   /// <summary>
	   /// Очистка предыдущих элементов управления для переменных из формулы первого потока.
	   /// </summary>
	   void ClearVariableControls() {
		   System::Collections::Generic::List<Control^>^ controlsToRemove = gcnew System::Collections::Generic::List<Control^>();

		   // Перебираем все элементы управления на форме
		   for each (Control ^ control in this->Controls) {
			   // Проверяем, является ли элемент текстовым полем или меткой для переменной
			   if (control->Name->StartsWith("txtVariable") || control->Name->StartsWith("label")) {
				   controlsToRemove->Add(control); // Добавляем элемент в список для удаления
			   }
		   }

		   // Удаляем элементы управления из списка с формы
		   for each (Control ^ control in controlsToRemove) {
			   this->Controls->Remove(control);
		   }
	   }


	   /// <summary>
	   /// Создание элементов управления для ввода значений переменных формулы первого потока.
	   /// </summary>
	   /// <param name="variables">Список переменных, извлечённых из выражения</param>
	   void CreateVariableControls(const std::vector<std::string>& variables) {
		   int yPos = 150; // Начальная позиция элемента по вертикали
		   int tabIndex = 1;

		   for (size_t i = 0; i < variables.size(); ++i) {
			   Label^ label = gcnew Label(); // Создание метки для отображения имени переменной
			   label->Text = gcnew String(variables[i].c_str()); // Установка текста метки в имя переменной
			   label->Location = Point(10, yPos); // Установка положения метки по вертикали
			   label->AutoSize = true; // Автоматическое определение размеров метки
			   label->Name = "label" + i.ToString(); // Уникальное имя для метки

			   TextBox^ textBox = gcnew TextBox(); // Создание текстового поля для ввода значения переменной
			   textBox->Name = "txtVariable" + i.ToString(); // Установка уникального имени для текстового поля
			   textBox->Location = Point(30, yPos); // Установка положения текстового поля по вертикали
			   textBox->TabIndex = tabIndex++; // Установка порядка перехода по элементам с клавиатуры
			   textBox->Size = Drawing::Size(30, 20); // Установка размеров текстового поля

			   this->Controls->Add(label); // Добавление метки на форму
			   this->Controls->Add(textBox); // Добавление текстового поля на форму

			   yPos += 30; // Перемещение следующего элемента вниз для отображения следующей переменной
		   }
	   }

	   
/// <summary>
/// Обработка изменения выбранной формулы из списка пользователем.
/// Устанавливает выбранную формулу в поле ввода формулы, создает элементы управления для ввода переменных.
/// </summary>
private: System::Void ChooseFormula_SelectedItemChanged(System::Object^ sender, System::EventArgs^ e) {
	System::String^ selectedFormula = ChooseFormula->SelectedItem->ToString(); // Получение выбранной формулы из списка

	FormulaEntering->Text = selectedFormula; // Установка выбранной формулы в поле для ввода

	std::string formula = msclr::interop::marshal_as<std::string>(selectedFormula); // Преобразование выбранной формулы в строку
	std::vector<std::string> variables = GetVariablesFromFormula(formula); // Получение списка переменных из выбранной формулы

	ClearVariableControls(); // Очистка старых элементов управления для ввода переменных, если они были

	// Создание новых элементов управления для ввода переменных
	CreateVariableControls(variables);
}


/// <summary>
/// Обработка нажатия кнопки открытия нового файла пользователем.
/// Открывает диалоговое окно для выбора файла, загружает формулы из выбранного файла.
/// </summary>
private: System::Void BtnOpenFile_Click(System::Object^ sender, System::EventArgs^ e) {
	OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog(); // Создание объекта диалогового окна для открытия файла

	openFileDialog1->Filter = "Text Files (*.txt)|*.txt"; // Установка фильтра для отображения только файлов формата .txt
	openFileDialog1->FilterIndex = 1; // Установка начального индекса фильтра

	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		// Если пользователь выбрал файл и нажал OK в диалоговом окне
		System::String^ selectedFile = openFileDialog1->FileName; // Получение пути к выбранному файлу

		selectedFilePath = msclr::interop::marshal_as<std::string>(selectedFile); // Преобразование пути в строку для работы с ним
		LoadFormulasFromFile(selectedFile); // Загрузка формул из выбранного файла
	}
}

	   /// <summary>
	   /// Обновляет данные в истории вычислений и списке формул для выбора, основываясь на содержимом файла.
	   /// </summary>
	   /// <param name="filePath">Путь к файлу, с которым выполняется работа</param>
	   void LoadFormulasFromFile(System::String^ filePath) {
		   System::IO::StreamReader^ file = gcnew System::IO::StreamReader(filePath); // Чтение файла

		   ChooseFormula->Items->Clear(); // Очистка списка формул для выбора
		   HistoryList->Items->Clear(); // Очистка истории вычислений

		   while (!file->EndOfStream) { // Пока не достигнут конец файла
			   System::String^ line = file->ReadLine(); // Чтение строки из файла
			   if (isValidExpressionForAdd(msclr::interop::marshal_as<std::string>(line)) && line->Length > 1) {
				   // Если строка из файла является корректным выражением для добавления и имеет длину больше 1
				   ChooseFormula->Items->Add(line); // Добавление строки в список формул для выбора
				   ChooseFormula2->Items->Add(line); // Добавление строки во второй список формул для выбора (если применимо)
			   }
			   HistoryList->Items->Add(line); // Добавление строки в историю вычислений
		   }

		   file->Close(); // Закрытие файла после чтения
	   }

	   
	   /// <summary>
	   /// создание узла для операнда
	   /// </summary>
	   /// <param name="operand">операнд</param>
	   /// <returns>узел</returns>
	   Node* createOperandNode(double operand) {
		   //преобразование числа в строку и сохранение его в качестве данных узла
		   return new Node(std::to_string(operand));
	   }

	   /// <summary>
	   /// получение операнда из узла
	   /// </summary>
	   /// <param name="node">узел</param>
	   /// <returns>операнд из узла</returns>
	   double getOperandValue(Node* node) {
		   //преобразование строки в число типа double
		   return std::stod(node->data);
	   }

	   /// <summary>
	   /// создание узла для оператора
	   /// </summary>
	   /// <param name="op">оператор</param>
	   /// <param name="left">ссылка на левый потомок</param>
	   /// <param name="right">ссылка на правый потомок</param>
	   /// <returns>узел</returns>
	   Node* createOperatorNode(const std::string& op, Node* left, Node* right) {
		   Node* node = new Node(op);
		   node->left = left;
		   node->right = right;
		   return node;
	   }

	   /// <summary>
	   /// Расставление приоритетов действий
	   /// </summary>
	   /// <param name="op">операнд действия</param>
	   /// <returns>Уровень приоритета</returns>
	   int getPriority(char op) {
		   if (op == '*' || op == '/') {
			   return 2;
		   }
		   else if (op == '+' || op == '-') {
			   return 1;
		   }
		   return 0;
	   }

	   /// <summary>
       /// Преобразует выражение в дерево для последующего вычисления значения.
       /// </summary>
       /// <param name="expression">Строка с выражением</param>
       /// <returns>Корень дерева</returns>
	   Node* parseExpression(const std::string& expression) {
		   std::stack<Node*> nodeStack; // Стек для хранения узлов дерева выражения
		   std::stack<char> opStack;    // Стек для хранения операторов (+, -, *, /)
		   std::string operand;         // Строка для сбора операндов (чисел) из выражения

		   for (size_t i = 0; i < expression.size(); ++i) {
			   char c = expression[i];

			   if (isspace(c)) { // Пропуск пробелов
				   continue;
			   }
			   else if (isdigit(c) || c == '.') { // Сбор числовых значений
				   if (isdigit(c))
					   operand += c;
				   else
					   operand += ',';
			   }
			   else { // Если символ - оператор или скобка
				   if (!operand.empty()) { // Если операнд не пустой, добавляем его в стек узлов
					   nodeStack.push(createOperandNode(std::stod(operand)));
					   operand.clear();
				   }

				   if (c == '(') { // Если символ - открывающая скобка, добавляем её в стек операторов
					   opStack.push(c);
				   }
				   else if (c == ')') { // Если символ - закрывающая скобка, выполняем операции до открывающей скобки
					   while (!opStack.empty() && opStack.top() != '(') {
						   // Обработка операций с узлами: получаем оператор, удаляем его из стека, создаем узел операции
						   char op = opStack.top();
						   opStack.pop();

						   if (nodeStack.size() < 2) {
							   // Если операндов недостаточно для операции, выводим сообщение об ошибке
							   System::Windows::Forms::MessageBox::Show("Ошибка: недостаточно операндов для операции " + gcnew String(1, op));
							   return nullptr;
						   }

						   Node* right = nodeStack.top();
						   nodeStack.pop();
						   Node* left = nodeStack.top();
						   nodeStack.pop();

						   nodeStack.push(createOperatorNode(std::string(1, op), left, right)); // Создаем узел операции и добавляем в стек узлов
					   }
					   if (!opStack.empty() && opStack.top() == '(') {
						   opStack.pop(); // Удаляем открывающую скобку из стека
					   }
					   else {
						   // Нет соответствующей открывающей скобки, выводим сообщение об ошибке
						   System::Windows::Forms::MessageBox::Show("Ошибка: не найдена открывающая скобка");
						   return nullptr;
					   }
				   }
				   else if (c == '+' || c == '-' || c == '*' || c == '/') { // Если символ - операция, выполняем операции в зависимости от приоритета
					   while (!opStack.empty() && opStack.top() != '(' && getPriority(opStack.top()) >= getPriority(c)) {
						   char op = opStack.top();
						   opStack.pop();

						   if (nodeStack.size() < 2) {
							   // Если операндов недостаточно для операции, выводим сообщение об ошибке
							   System::Windows::Forms::MessageBox::Show("Ошибка: недостаточно операндов для операции " + gcnew String(1, op));
							   return nullptr;
						   }

						   Node* right = nodeStack.top();
						   nodeStack.pop();
						   Node* left = nodeStack.top();
						   nodeStack.pop();

						   nodeStack.push(createOperatorNode(std::string(1, op), left, right)); // Создаем узел операции и добавляем в стек узлов
					   }
					   opStack.push(c); // Добавляем текущий оператор в стек операторов
				   }
				   else {
					   // Любой другой символ считается некорректным в выражении, выводим сообщение об ошибке
					   System::Windows::Forms::MessageBox::Show("Ошибка: неизвестный символ");
					   return nullptr;
				   }
			   }
		   }

		   if (!operand.empty()) { // Если остался последний операнд
			   nodeStack.push(createOperandNode(std::stod(operand)));
		   }

		   // Завершение вычислений: выполнение операций, пока стек операций не опустеет
		   while (!opStack.empty()) {
			   char op = opStack.top();
			   opStack.pop();

			   if (nodeStack.size() < 2) {
				   // Если операндов недостаточно для операции, выводим сообщение об ошибке
				   System::Windows::Forms::MessageBox::Show("Ошибка: недостаточно операндов для операции " + gcnew String(1, op));
				   return nullptr;
			   }

			   Node* right = nodeStack.top();
			   nodeStack.pop();
			   Node* left = nodeStack.top();
			   nodeStack.pop();

			   nodeStack.push(createOperatorNode(std::string(1, op), left, right)); // Создаем узел операции и добавляем в стек узлов
		   }

		   // Проверка на наличие одного корня в стеке узлов
		   if (nodeStack.size() != 1) {
			   // Если количество узлов не равно одному, выводим сообщение об ошибке
			   System::Windows::Forms::MessageBox::Show("Ошибка в выражении");
			   return nullptr;
		   }

		   return nodeStack.top(); // Возвращаем корень дерева
	   }

	   /// <summary>
	   /// Выполнение простых вычислений
       /// <summary>
       /// Выполняет арифметическую операцию между двумя значениями.
       /// </summary>
       /// <param name="a">Значение первой переменной</param>
       /// <param name="b">Значение второй переменной</param>
       /// <param name="op">Действие для выполнения (+, -, *, /)</param>
       /// <returns>Результат операции</returns>
	   double calculate(double a, double b, char op) {
		   switch (op) {
		   case '+': // Сложение
			   return a + b;
		   case '-': // Вычитание
			   return a - b;
		   case '*': // Умножение
			   return a * b;
		   case '/': // Деление
			   if (b != 0) {
				   return a / b; // Если делитель не ноль, выполняет деление
			   }
			   else {
				   System::Windows::Forms::MessageBox::Show("Ошибка: деление на ноль"); // Вывод сообщения об ошибке деления на ноль
			   }
		   default: // Обработка некорректной операции
			   System::Windows::Forms::MessageBox::Show("Ошибка: некорректная операция"); // Вывод сообщения об ошибке для некорректной операции
			   return 0; // Возвращает 0 в случае некорректной операции
		   }
	   }


	   /// <summary>
	   /// Выполняет вычисление значения выражения, представленного в виде дерева.
	   /// </summary>
	   /// <param name="root">Ссылка на корневой узел дерева выражения</param>
	   /// <returns>Результат вычислений</returns>
	   double evaluateExpressionTree(Node* root) {
		   if (root) {
			   // Если узел - лист (не имеет дочерних узлов), возвращает числовое значение узла
			   if (!root->left && !root->right) {
				   return std::stod(root->data); // Преобразует строку в число и возвращает ее значение
			   }
			   else {
				   // Рекурсивно вычисляет левое и правое поддеревья и выполняет операцию между ними
				   double leftValue = evaluateExpressionTree(root->left);
				   double rightValue = evaluateExpressionTree(root->right);
				   return calculate(leftValue, rightValue, root->data[0]); // Выполняет операцию между узлами
			   }
		   }
		   return 0.0; // Возвращает 0, если узел не существует
	   }


	   /// <summary>
	   /// Записывает в файл значения переменных, введенные пользователем.
	   /// </summary>
	   /// <param name="variableValues">Значения переменных</param>
	   /// <param name="filename">Название файла для записи</param>
	   void writeVariablesToFile(const std::map<std::string, double>& variableValues, const std::string& filename) {
		   std::ofstream outputFile(selectedFilePath, std::ios::app); // Открываем файл для записи

		   if (outputFile.is_open()) {
			   // Записываем значения переменных в файл в формате "переменная=значение"
			   for (const auto& pair : variableValues) {
				   outputFile << pair.first << "=" << pair.second << "\n";
			   }
			   outputFile.close(); // Закрываем файл после записи
		   }
		   else {
			   // Если не удалось открыть файл для записи, выводим сообщение об ошибке
			   System::Windows::Forms::MessageBox::Show("Ошибка открытия файла");
		   }
	   }


	   /// <summary>
	   /// Функция для обработки формулы и записи результата в файл
       /// <summary>
       /// Обрабатывает формулу и вычисляет результат для данной формулы, записывая результат в файл.
       /// </summary>
       /// <param name="num">Номер потока (1 или 2)</param>
       /// <param name="root">Корень дерева для вычислений</param>
       /// <param name="expression">Формула</param>
       /// <param name="variableValues">Значения переменных</param>
	   void processFormula(int num, Node* root, std::string expression, std::map<std::string, double> variableValues) {
		   // Вычисляем результат для данной формулы с помощью дерева выражения
		   double result = evaluateExpressionTree(root);

		   // Захватываем мьютекс для безопасной записи в файл
		   fileMutex.lock();

		   // Открываем файл для записи результата
		   std::ofstream outFile(selectedFilePath, std::ios::app);
		   if (outFile.is_open()) {
			   outFile << expression << "\n"; // Записываем формулу в файл
			   writeVariablesToFile(variableValues, selectedFilePath); // Записываем значения переменных в файл

			   try {
				   if (num == 1)
					   result1 = result; // Записываем результат в переменную result1 для первого потока
				   else
					   result2 = result; // Записываем результат в переменную result2 для второго потока

				   outFile << result << "\n"; // Записываем результат в файл
			   }
			   catch (const std::runtime_error& e) {
				   // Обработка ошибки при вычислении результата
				   System::Windows::Forms::MessageBox::Show("Ошибка");
			   }
			   outFile.close(); // Закрываем файл
		   }
		   fileMutex.unlock(); // Освобождаем мьютекс
	   }


	   /// <summary>
	   /// Выполняет вычисления первым потоком.
	   /// </summary>
	   void PerformCalculation() {
		   setlocale(LC_ALL, "Russian"); // Устанавливаем русскую локаль для работы с текстовыми данными

		   // Получаем выражение из текстового поля ввода
		   std::string expression = msclr::interop::marshal_as<std::string>(FormulaEntering->Text);

		   // Проверяем валидность выражения
		   if (isValidExpression(expression)) {
			   std::vector<std::string> variables = GetVariablesFromFormula(expression); // Получаем список переменных из выражения

			   // Создаём словарь для хранения значений переменных
			   std::map<std::string, double> variableValues;

			   // Собираем значения переменных из текстовых полей ввода
			   for (size_t i = 0; i < variables.size(); ++i) {
				   TextBox^ textBox = dynamic_cast<TextBox^>(this->Controls[gcnew String(("txtVariable" + std::to_string(i)).c_str())]);
				   if (textBox != nullptr) {
					   double value;
					   if (Double::TryParse(textBox->Text, value)) {
						   variableValues[variables[i]] = value; // Сохраняем значение переменной в словаре
					   }
					   else {
						   // Обработка ошибки: введено некорректное значение переменной
						   MessageBox::Show("Некорректное значение для переменной " + gcnew String(variables[i].c_str()));
						   return;
					   }
				   }
				   else {
					   // Обработка ошибки: элемент управления не найден
					   MessageBox::Show("Элемент управления не найден для переменной " + gcnew String(variables[i].c_str()));
					   return;
				   }
			   }

			   // Открываем файл для записи (если selectedFilePath содержит путь к файлу)
			   std::ofstream outputFile(selectedFilePath, std::ios::app);

			   // Заменяем переменные в выражении на их числовые значения
			   std::string substitutedExpression = SubstituteVariables(expression, variableValues);

			   // Парсим выражение и создаём дерево выражения
			   Node* root = parseExpression(substitutedExpression); // Предположим, что есть функция для создания дерева выражения

			   // Выполняем обработку формулы (предполагаем, что processFormula обрабатывает выражение)
			   processFormula(1, root, expression, variableValues);

		   }
		   else {
			   // Действия при ошибке в выражении
			   System::Windows::Forms::MessageBox::Show("Ошибка в выражении2");
		   }
	   }


	   /// <summary>
	   /// Выполняет вычисления вторым потоком.
	   /// </summary>
	   void PerformCalculation2() {
		   setlocale(LC_ALL, "Russian"); // Устанавливаем русскую локаль для работы с текстовыми данными

		   // Получаем выражение из текстового поля ввода
		   std::string expression = msclr::interop::marshal_as<std::string>(FormulaEntering2->Text);

		   // Проверяем валидность выражения
		   if (isValidExpression(expression)) {
			   std::vector<std::string> variables = GetVariablesFromFormula(expression); // Получаем список переменных из выражения

			   // Создаём словарь для хранения значений переменных
			   std::map<std::string, double> variableValues;

			   // Собираем значения переменных из текстовых полей ввода
			   for (size_t i = 0; i < variables.size(); ++i) {
				   TextBox^ textBox = dynamic_cast<TextBox^>(this->Controls[gcnew String(("2txtVariable" + std::to_string(i)).c_str())]);
				   if (textBox != nullptr) {
					   double value;
					   if (Double::TryParse(textBox->Text, value)) {
						   variableValues[variables[i]] = value; // Сохраняем значение переменной в словаре
					   }
					   else {
						   // Обработка ошибки: введено некорректное значение переменной
						   MessageBox::Show("Некорректное значение для переменной " + gcnew String(variables[i].c_str()));
						   return;
					   }
				   }
				   else {
					   // Обработка ошибки: элемент управления не найден
					   MessageBox::Show("Элемент управления не найден для переменной " + gcnew String(variables[i].c_str()));
					   return;
				   }
			   }

			   // Открываем файл для записи (предполагая, что selectedFilePath содержит путь к файлу)
			   std::ofstream outputFile(selectedFilePath, std::ios::app);

			   // Заменяем переменные в выражении на их числовые значения
			   std::string substitutedExpression = SubstituteVariables(expression, variableValues);

			   // Парсим выражение и создаём дерево выражения
			   Node* root = parseExpression(substitutedExpression); // Предполагаем, что есть функция для создания дерева выражения

			   // Выполняем обработку формулы (предполагаем, что processFormula обрабатывает выражение)
			   processFormula(2, root, expression, variableValues);

		   }
		   else {
			   // Действия при ошибке в выражении
			   System::Windows::Forms::MessageBox::Show("Ошибка в выражении3");
		   }
	   }


	   /// <summary>
	   /// Заменяет переменные в формуле на числовые значения с использованием предоставленных значений переменных.
	   /// </summary>
	   /// <param name="expression">Исходная формула</param>
	   /// <param name="variableValues">Значения переменных</param>
	   /// <returns>Формула с заменёнными переменными на их числовые значения</returns>
	   std::string SubstituteVariables(const std::string& expression, const std::map<std::string, double>& variableValues) {
		   std::string substitutedExpression = expression; // Копируем исходную формулу для замены переменных

		   // Для каждой переменной из предоставленных значений
		   for (const auto& pair : variableValues) {
			   size_t pos = 0;
			   // Пока переменная найдена в формуле
			   while ((pos = substitutedExpression.find(pair.first, pos)) != std::string::npos) {
				   std::ostringstream oss;
				   oss.precision(15); // Устанавливаем точность для числового значения переменной
				   oss << std::fixed << pair.second; // Преобразуем значение переменной в строку
				   substitutedExpression.replace(pos, pair.first.length(), oss.str()); // Заменяем переменную на числовое значение
				   pos += oss.str().length(); // Обновляем позицию для поиска следующей переменной
			   }
		   }
		   return substitutedExpression; // Возвращаем формулу с заменёнными значениями переменных
	   }



	   /// <summary>
	   /// Обработчик события нажатия на кнопку "Рассчитать". Создает два потока для вычислений,
	   /// ожидает их завершения, выводит результаты в соответствующие текстовые поля и перезагружает формулы из файла.
	   /// </summary>
	   /// <param name="sender">Объект, инициировавший событие</param>
	   /// <param name="e">Аргументы события</param>
private: System::Void BtnCount_Click(System::Object^ sender, System::EventArgs^ e) {
	// Создание двух потоков для выполнения вычислений
	Thread^ thread1 = gcnew Thread(gcnew ThreadStart(this, &MainForm::PerformCalculation));
	Thread^ thread2 = gcnew Thread(gcnew ThreadStart(this, &MainForm::PerformCalculation2));

	// Запуск потоков
	thread1->Start();
	thread2->Start();

	// Ожидание завершения работы потоков
	thread1->Join();
	thread2->Join();

	// Создание текстовых полей для вывода результатов первого и второго потоков
	TextBox^ resultTextBox = gcnew TextBox();
	TextBox^ resultTextBox2 = gcnew TextBox();

	// Вывод результата для первого потока
	// Создание и настройка textBox для вывода результата первого потока
	resultTextBox->Size = System::Drawing::Size(120, 20);
	resultTextBox->Location = System::Drawing::Point(75, 377);
	resultTextBox->Text = result1.ToString("F5"); // result1 - результат вычислений первого потока
	this->Controls->Add(resultTextBox);

	// Вывод результата для второго потока
	// Создание и настройка textBox для вывода результата второго потока
	resultTextBox2->Size = System::Drawing::Size(120, 20);
	resultTextBox2->Location = System::Drawing::Point(595, 377);
	resultTextBox2->Text = result2.ToString("F5"); // result2 - результат вычислений второго потока
	this->Controls->Add(resultTextBox2);

	// Перезагрузка формул из файла
	LoadFormulasFromFile(gcnew System::String(selectedFilePath.c_str()));
}


/// <summary>
/// Обработчик события нажатия на кнопку 1. Проверяет валидность выражения, извлекает переменные и обновляет контролы ввода переменных.
/// </summary>
/// <param name="sender">Объект, инициировавший событие</param>
/// <param name="e">Аргументы события</param>
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	// Преобразование текста введенной формулы в строку C++
	std::string formula = msclr::interop::marshal_as<std::string>(FormulaEntering->Text);

	// Проверка валидности выражения
	if (isValidExpression(formula)) {
		// Извлечение переменных из формулы
		std::vector<std::string> variables = GetVariablesFromFormula(formula);

		// Очистка предыдущих контролов для ввода переменных
		ClearVariableControls();

		// Создание новых контролов для ввода переменных на основе извлеченных переменных
		CreateVariableControls(variables);
	}
	else {
		// Вывод сообщения пользователю при ошибке в выражении
		System::Windows::Forms::MessageBox::Show("Ошибка в выражении");
	}
}


/// <summary>
/// Обработчик события нажатия на кнопку 2. Проверяет валидность выражения, извлекает переменные и обновляет контролы ввода переменных.
/// </summary>
/// <param name="sender">Объект, инициировавший событие</param>
/// <param name="e">Аргументы события</param>
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	// Преобразование текста введенной формулы в строку C++
	std::string formula = msclr::interop::marshal_as<std::string>(FormulaEntering2->Text);

	// Проверка валидности выражения
	if (isValidExpression(formula)) {
		// Извлечение переменных из формулы
		std::vector<std::string> variables = GetVariablesFromFormula(formula);

		// Очистка предыдущих контролов для ввода переменных
		ClearVariableControls2();

		// Создание новых контролов для ввода переменных на основе извлеченных переменных
		CreateVariableControls2(variables);
	}
	else {
		// Вывод сообщения пользователю при ошибке в выражении
		System::Windows::Forms::MessageBox::Show("Ошибка в выражении");
	}
}


	   /// <summary>
       /// Создание текстовых полей для ввода значений переменных выражения второго потока
       /// </summary>
       /// <param name="variables">список переменных, извлечённый из формулы</param>
	   void CreateVariableControls2(const std::vector<std::string>& variables) {
		   int yPos = 150;    // Начальная позиция по вертикали для размещения элементов управления
		   int tabIndex = 1;  // Начальный индекс для переключения между элементами управления (Tab Order)

		   // Проход по списку переменных для создания текстовых меток и текстовых полей ввода
		   for (size_t i = 0; i < variables.size(); ++i) {
			   Label^ label = gcnew Label();    // Создание метки для отображения имени переменной
			   label->Text = gcnew String(variables[i].c_str());  // Установка текста метки
			   label->Location = Point(510, yPos);    // Задание позиции метки по горизонтали и вертикали
			   label->AutoSize = true;   // Установка автоматического размера метки
			   label->Name = "2label" + i.ToString();  // Задание имени метки

			   TextBox^ textBox = gcnew TextBox(); // Создание текстового поля для ввода значения переменной
			   textBox->Name = "2txtVariable" + i.ToString(); // Установка имени текстового поля
			   textBox->Location = Point(530, yPos);   // Задание позиции текстового поля по горизонтали и вертикали
			   textBox->TabIndex = tabIndex++; // Установка индекса переключения для последовательного фокусирования
			   textBox->Size = Drawing::Size(30, 20);   // Установка размера текстового поля

			   // Добавление метки и текстового поля в контейнер элементов управления формы
			   this->Controls->Add(label);
			   this->Controls->Add(textBox);

			   yPos += 30; // Перемещение на следующую позицию по вертикали для следующего элемента
		   }
	   }


	   /// <summary>
	   /// Удаление предыдущих окон для ввода переменных второго потока
	   /// </summary>
	   void ClearVariableControls2() {
		   // Создание списка элементов управления, которые нужно удалить
		   System::Collections::Generic::List<Control^>^ controlsToRemove = gcnew System::Collections::Generic::List<Control^>();

		   // Поиск и добавление элементов управления для удаления
		   for each (Control ^ control in this->Controls) {
			   // Проверка названий объектов, которые предполагается удалить (с именами, начинающимися на "2txtVariable" или "2label")
			   if (control->Name->StartsWith("2txtVariable") || control->Name->StartsWith("2label")) {
				   controlsToRemove->Add(control); // Добавление элементов управления в список для удаления
			   }
		   }

		   // Удаление элементов управления из родительского контейнера
		   for each (Control ^ control in controlsToRemove) {
			   this->Controls->Remove(control); // Удаление элементов из списка контролов
		   }
	   }

	   // Обработчик изменения выбранного элемента в списке формул (второй поток)
private: System::Void ChooseFormula2_SelectedItemChanged(System::Object^ sender, System::EventArgs^ e) {
	try {
		// Получение выбранной формулы из списка формул второго потока
		System::String^ selectedFormula = ChooseFormula2->SelectedItem->ToString();

		// Отображение выбранной формулы в соответствующем поле ввода
		FormulaEntering2->Text = selectedFormula;

		// Преобразование выбранной формулы в строку C++
		std::string formula = msclr::interop::marshal_as<std::string>(selectedFormula);

		// Получение переменных из выбранной формулы
		std::vector<std::string> variables = GetVariablesFromFormula(formula);

		// Очистка предыдущего списка элементов управления для переменных второго потока
		ClearVariableControls2();

		// Создание элементов управления для переменных на основе списка переменных
		CreateVariableControls2(variables);
	}
	catch (Exception^ ex) {
		// Обработка возможных исключений и отображение сообщения об ошибке
		MessageBox::Show("Ошибка при выборе формулы: " + ex->Message, "Ошибка");
	}
}

// Обработчик события нажатия кнопки "Создать новый файл"
private: System::Void BtnNewFile_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		// Запрос у пользователя имени и пути для нового файла через диалог сохранения
		SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
		saveFileDialog1->Filter = "Text Files (*.txt)|*.txt"; // Фильтр для файлов .txt
		saveFileDialog1->Title = "Save a Text File"; // Заголовок диалога сохранения

		// Если пользователь выбрал файл и подтвердил сохранение
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			String^ filePath = saveFileDialog1->FileName; // Получение пути к выбранному файлу

			// Создание нового .txt файла по указанному пути
			std::ofstream file(msclr::interop::marshal_as<std::string>(filePath));
			file.close(); // Закрытие файла
			selectedFilePath = msclr::interop::marshal_as<std::string>(filePath); // Сохранение пути для последующего использования
			LoadFormulasFromFile(filePath); // Загрузка формул из созданного файла

			// Отображение сообщения об успешном создании файла
			MessageBox::Show("Файл успешно создан.");
		}
	}
	catch (Exception^ ex) {
		// Обработка возможных исключений и отображение сообщения об ошибке
		MessageBox::Show("Ошибка при создании файла: " + ex->Message, "Ошибка");
	}
}
};

}
