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

	//����������, � ������� ����� ��������� ���������� ���������� ��� ������������ ������ � �����
	double result1, result2;

	//��������� ��� ���������� ������ ��� ����������
	struct Node {
		std::string data;
		Node* left;
		Node* right;
		Node(const std::string& data) : data(data), left(nullptr), right(nullptr) {}
	};

	std::mutex fileMutex; //������� ��� ����������� ������� � �����
	std::string selectedFilePath = "formulas.txt"; //�������� �����, � ������� � ������ ������ �������� ������������

	/// <summary>
	/// ������ ��� MainForm
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
		/// ���������� ��� ������������ �������.
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
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
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
			this->LblEnter->Text = L"���� �������";
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
			this->LblChoose->Text = L"����� �������";
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
			this->LblHistory->Text = L"������� ����������";
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
			this->LblMeaning->Text = L"�������� ����������";
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
			this->BtnNewFile->Text = L"����� ����";
			this->BtnNewFile->UseVisualStyleBackColor = true;
			this->BtnNewFile->Click += gcnew System::EventHandler(this, &MainForm::BtnNewFile_Click);
			// 
			// BtnOpenFile
			// 
			this->BtnOpenFile->Location = System::Drawing::Point(3, 3);
			this->BtnOpenFile->Name = L"BtnOpenFile";
			this->BtnOpenFile->Size = System::Drawing::Size(105, 31);
			this->BtnOpenFile->TabIndex = 0;
			this->BtnOpenFile->Text = L"������� ����";
			this->BtnOpenFile->UseVisualStyleBackColor = true;
			this->BtnOpenFile->Click += gcnew System::EventHandler(this, &MainForm::BtnOpenFile_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 47);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(83, 26);
			this->button1->TabIndex = 12;
			this->button1->Text = L"���������";
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
			this->BtnCount->Text = L"����������";
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
			this->LblEnter2->Text = L"���� �������";
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
			this->button2->Text = L"���������";
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
			this->LblChoose2->Text = L"����� �������";
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
			this->LblMeaning2->Text = L"�������� ����������";
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
			this->Text = L" �����������";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->tableLayoutPanel2->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
/// <summary>
/// ����� ��� ���������� ���� ����� - ��������� ������ �� ����� "formulas.txt" � ������� �������� � ���� ������ ������
/// </summary>
/// <param name="sender">������-��������� �������</param>
/// <param name="e">��������� �������</param>
private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	System::IO::StreamReader^ file;

	try {
		file = gcnew System::IO::StreamReader("formulas.txt"); // �������� ������� ���� ��� ������
	}
	catch (System::IO::FileNotFoundException^) {
		file = gcnew System::IO::StreamReader("formulas.txt", true); // ���� ���� �����������, ������� �����
	}

	// ������ ����� � ���������� ����� � ListBox, �������������� �� �������
	while (!file->EndOfStream) {
		System::String^ line = file->ReadLine(); // ������ ������ �� �����
		HistoryList->Items->Add(line); // ���������� ������ � ������ ������� ��������

		// �������� ������ �� ������������ ������� � ���������� � ������ ������ ��� ����� �������
		if (isValidExpressionForAdd(msclr::interop::marshal_as<std::string>(line)) && line->Length > 1) {
			ChooseFormula->Items->Add(line); // ���������� � ������ ������ ������� ������
			ChooseFormula2->Items->Add(line); // ���������� � ������ ������ ������� ������
		}
	}

	file->Close(); // �������� ����� ����� ������ ������
	Wellcome();
}

	private:
		
		/// <summary>
		/// �������� �� ������ ����������� �������
		/// </summary>
		/// <param name="c">������</param>
		/// <returns>true ���� ��� ����������� ������, false � ��������� ������</returns>
		bool isOpeningBracket(char c) {
			return c == '(';
		}

		/// <summary>
		/// �������� �� ������ ����������� �������
		/// </summary>
		/// <param name="c">������</param>
		/// <returns>true ���� ��� ����������� ������, false � ��������� ������</returns>
		bool isClosingBracket(char c) {
			return c == ')';
		}

		/// <summary>
		/// �������� �� ������ ����������
		/// </summary>
		/// <param name="c">������</param>
		/// <returns>true ���� ��������, false � ��������� ������</returns>
		bool isOperator(char c) {
			return (c == '+' || c == '-' || c == '*' || c == '/');
		}

		/// <summary>
		/// �������� �� ������ ������ �������� �����
		/// </summary>
		/// <param name="c">������</param>
		/// <returns>true ���� ��������, false � ��������� ������</returns>
		bool isNumericChar(char c) {
			return (isdigit(c) || c == '.' || c == '-');
		}

		/// <summary>
		/// �������� �� ������ ���������
		/// </summary>
		/// <param name="c">������</param>
		/// <returns>true ���� �������, false � ��������� ������</returns>
		bool isOperand(char c) {
			return std::isdigit(c) || std::isalpha(c);
		}

		/// <summary>
		/// ��������, �������� �� �������� ������� ���������� (��� ���������, ��� ���������� �� �����)
		/// </summary>
		/// <param name="expression">�������� ���������</param>
		/// <returns>true ���� ��������� ���������, false ���� �� ���������</returns>
		bool isValidExpressionForAdd(const std::string& expression) {
			std::stack<char> brackets; // ���� ��� ������������ ������
			char previousChar = '\0'; // ���������� ��� �������� ����������� �������

			for (size_t i = 0; i < expression.length(); ++i) {
				// �������� �������� �������

				if (isOpeningBracket(expression[i])) { // ���� ��� ����������� ������
					brackets.push(expression[i]); // �������� � ����

				}
				else if (isClosingBracket(expression[i])) { // ���� ��� ����������� ������
					if (brackets.empty() || !isOpeningBracket(brackets.top())) { // ���������, ��� ���� ��������������� ����������� ������
						return false; // ���� ���, ��������� �� ���������
					}
					brackets.pop(); // ����� ������� ��������������� ����������� ������ �� �����

				}
				else if (isOperator(expression[i])) { // ���� ��� ��������
					if (i == 0 || i == expression.length() - 1) { // ���������, ��� �������� �� ��������� � ������ ��� � ����� ���������
						return false;
					}
					if (isOperator(previousChar)) { // ���������, ��� ���������� ������ �� �������� ����������
						return false;
					}

				}
				else if (isOperand(expression[i])) { // ���� ��� �������
					if (isOperand(previousChar)) { // ���������, ��� ���������� ������ �� �������� ���������
						return false;
					}

				}
				else {
					return false; // ���� ������ �� �������� �� �������, �� ����������, �� ���������, ��������� �� ���������
				}

				previousChar = expression[i]; // ��������� ���������� ������
			}

			if (!brackets.empty()) { // ���������, �������� �� �������� ������
				return false;
			}

			return true; // ���������� true, ���� ��� ������� �������� ��������� �������
		}

		/// <summary>
		/// ��������, �������� �� �������� ������� ���������� (� �����������)
		/// </summary>
		/// <param name="expression">�������� ���������</param>
		/// <returns>true, ���� ��������� ���������; false, ���� �����������</returns>
		bool isValidExpression(const std::string& expression) {
			std::stack<Node*> nodeStack; // ���� ��� �������� ����� ������ ���������
			std::stack<char> opStack;    // ���� ��� �������� ���������� (+, -, *, /)
			std::string operand;         // ������ ��� ����� ��������� (�����) �� ���������

			for (size_t i = 0; i < expression.size(); ++i) {
				char c = expression[i];

				if (isspace(c)) { // ���������� �������
					continue;
				}
				else if (isdigit(c) || c == '.') { // ���� ������ - ����� ��� �����, ��������� � ��������
					if (isdigit(c))
						operand += c;

				}
				else { // ���� ������ - �������� ��� ������
					if (!operand.empty()) { // ���� ��� ������ �������, ��������� ��� � ���� �����
						nodeStack.push(createOperandNode(std::stod(operand)));
						operand.clear();
					}

					if (c == '(') {
						opStack.push(c); // ���� ������ - ����������� ������, ��������� � � ���� ����������
					}
					else if (c == ')') { // ���� ������ - ����������� ������
						while (!opStack.empty() && opStack.top() != '(') {
							char op = opStack.top();
							opStack.pop();

							if (nodeStack.size() < 2) {
								return false; // ���� ��������� ������������ ��� ��������, ��������� �����������
							}

							Node* right = nodeStack.top();
							nodeStack.pop();
							Node* left = nodeStack.top();
							nodeStack.pop();

							nodeStack.push(createOperatorNode(std::string(1, op), left, right)); // ������� ���� �������� � ��������� � ���� �����
						}
						if (!opStack.empty()) {
							opStack.pop(); // ������� ����������� ������ �� ����� ����������
						}
						else {
							return false; // ��� ��������������� ����������� ������, ��������� �����������
						}
					}
					else if (c == '+' || c == '-' || c == '*' || c == '/') { // ���� ������ - ��������
						while (!opStack.empty() && opStack.top() != '(' && getPriority(opStack.top()) >= getPriority(c)) {
							char op = opStack.top();
							opStack.pop();

							if (nodeStack.size() < 2) {
								return false; // ���� ��������� ������������ ��� ��������, ��������� �����������
							}

							Node* right = nodeStack.top();
							nodeStack.pop();
							Node* left = nodeStack.top();
							nodeStack.pop();

							nodeStack.push(createOperatorNode(std::string(1, op), left, right)); // ������� ���� �������� � ��������� � ���� �����
						}
						opStack.push(c); // ��������� ������� �������� � ���� ����������
					}
					else {
						return true; // ����� ������ ������ ��������� ������������ � ���������
					}
				}
			}
		}


private: System::Void vScrollBar1_Scroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e) {
	//����������� ��������� � ���� � �������� ����������
	HistoryList->TopIndex = vScrollBar1->Value;
}
	   /// <summary>
       /// ��������� ��� ����������, ��� ������� ����� �������� ��������, �� �������.
       /// </summary>
       /// <param name="formula">������ �������</param>
       /// <returns>������ ��������������� ����������</returns>
	   std::vector<std::string> GetVariablesFromFormula(const std::string& formula) {
		   std::vector<std::string> variables;

		   //������ �� ������ �������
		   size_t i = 0;
		   while (i < formula.length()) {
			   std::string variable;

			   //������� �������� � �������� ��������
			   while (i < formula.length() && (std::isspace(formula[i]) || formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/' || formula[i] == '(' || formula[i] == ')' || isdigit(formula[i]))) {
				   i++;
			   }

			   //������������ �������������� ����������
			   while (i < formula.length() && (std::isalpha(formula[i]) || std::isdigit(formula[i]))) {
				   variable += formula[i];
				   i++;
			   }

			   //���������� ���������� � ������, ���� ��� �� ������
			   if (!variable.empty()) {
				   variables.push_back(variable);
			   }
		   }

		   return variables;
	   }


	   /// <summary>
	   /// ������� ���������� ��������� ���������� ��� ���������� �� ������� ������� ������.
	   /// </summary>
	   void ClearVariableControls() {
		   System::Collections::Generic::List<Control^>^ controlsToRemove = gcnew System::Collections::Generic::List<Control^>();

		   // ���������� ��� �������� ���������� �� �����
		   for each (Control ^ control in this->Controls) {
			   // ���������, �������� �� ������� ��������� ����� ��� ������ ��� ����������
			   if (control->Name->StartsWith("txtVariable") || control->Name->StartsWith("label")) {
				   controlsToRemove->Add(control); // ��������� ������� � ������ ��� ��������
			   }
		   }

		   // ������� �������� ���������� �� ������ � �����
		   for each (Control ^ control in controlsToRemove) {
			   this->Controls->Remove(control);
		   }
	   }


	   /// <summary>
	   /// �������� ��������� ���������� ��� ����� �������� ���������� ������� ������� ������.
	   /// </summary>
	   /// <param name="variables">������ ����������, ����������� �� ���������</param>
	   void CreateVariableControls(const std::vector<std::string>& variables) {
		   int yPos = 150; // ��������� ������� �������� �� ���������
		   int tabIndex = 1;

		   for (size_t i = 0; i < variables.size(); ++i) {
			   Label^ label = gcnew Label(); // �������� ����� ��� ����������� ����� ����������
			   label->Text = gcnew String(variables[i].c_str()); // ��������� ������ ����� � ��� ����������
			   label->Location = Point(10, yPos); // ��������� ��������� ����� �� ���������
			   label->AutoSize = true; // �������������� ����������� �������� �����
			   label->Name = "label" + i.ToString(); // ���������� ��� ��� �����

			   TextBox^ textBox = gcnew TextBox(); // �������� ���������� ���� ��� ����� �������� ����������
			   textBox->Name = "txtVariable" + i.ToString(); // ��������� ����������� ����� ��� ���������� ����
			   textBox->Location = Point(30, yPos); // ��������� ��������� ���������� ���� �� ���������
			   textBox->TabIndex = tabIndex++; // ��������� ������� �������� �� ��������� � ����������
			   textBox->Size = Drawing::Size(30, 20); // ��������� �������� ���������� ����

			   this->Controls->Add(label); // ���������� ����� �� �����
			   this->Controls->Add(textBox); // ���������� ���������� ���� �� �����

			   yPos += 30; // ����������� ���������� �������� ���� ��� ����������� ��������� ����������
		   }
	   }

	   
/// <summary>
/// ��������� ��������� ��������� ������� �� ������ �������������.
/// ������������� ��������� ������� � ���� ����� �������, ������� �������� ���������� ��� ����� ����������.
/// </summary>
private: System::Void ChooseFormula_SelectedItemChanged(System::Object^ sender, System::EventArgs^ e) {
	System::String^ selectedFormula = ChooseFormula->SelectedItem->ToString(); // ��������� ��������� ������� �� ������

	FormulaEntering->Text = selectedFormula; // ��������� ��������� ������� � ���� ��� �����

	std::string formula = msclr::interop::marshal_as<std::string>(selectedFormula); // �������������� ��������� ������� � ������
	std::vector<std::string> variables = GetVariablesFromFormula(formula); // ��������� ������ ���������� �� ��������� �������

	ClearVariableControls(); // ������� ������ ��������� ���������� ��� ����� ����������, ���� ��� ����

	// �������� ����� ��������� ���������� ��� ����� ����������
	CreateVariableControls(variables);
}


/// <summary>
/// ��������� ������� ������ �������� ������ ����� �������������.
/// ��������� ���������� ���� ��� ������ �����, ��������� ������� �� ���������� �����.
/// </summary>
private: System::Void BtnOpenFile_Click(System::Object^ sender, System::EventArgs^ e) {
	OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog(); // �������� ������� ����������� ���� ��� �������� �����

	openFileDialog1->Filter = "Text Files (*.txt)|*.txt"; // ��������� ������� ��� ����������� ������ ������ ������� .txt
	openFileDialog1->FilterIndex = 1; // ��������� ���������� ������� �������

	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		// ���� ������������ ������ ���� � ����� OK � ���������� ����
		System::String^ selectedFile = openFileDialog1->FileName; // ��������� ���� � ���������� �����

		selectedFilePath = msclr::interop::marshal_as<std::string>(selectedFile); // �������������� ���� � ������ ��� ������ � ���
		LoadFormulasFromFile(selectedFile); // �������� ������ �� ���������� �����
	}
}

	   /// <summary>
	   /// ��������� ������ � ������� ���������� � ������ ������ ��� ������, ����������� �� ���������� �����.
	   /// </summary>
	   /// <param name="filePath">���� � �����, � ������� ����������� ������</param>
	   void LoadFormulasFromFile(System::String^ filePath) {
		   System::IO::StreamReader^ file = gcnew System::IO::StreamReader(filePath); // ������ �����

		   ChooseFormula->Items->Clear(); // ������� ������ ������ ��� ������
		   HistoryList->Items->Clear(); // ������� ������� ����������

		   while (!file->EndOfStream) { // ���� �� ��������� ����� �����
			   System::String^ line = file->ReadLine(); // ������ ������ �� �����
			   if (isValidExpressionForAdd(msclr::interop::marshal_as<std::string>(line)) && line->Length > 1) {
				   // ���� ������ �� ����� �������� ���������� ���������� ��� ���������� � ����� ����� ������ 1
				   ChooseFormula->Items->Add(line); // ���������� ������ � ������ ������ ��� ������
				   ChooseFormula2->Items->Add(line); // ���������� ������ �� ������ ������ ������ ��� ������ (���� ���������)
			   }
			   HistoryList->Items->Add(line); // ���������� ������ � ������� ����������
		   }

		   file->Close(); // �������� ����� ����� ������
	   }

	   
	   /// <summary>
	   /// �������� ���� ��� ��������
	   /// </summary>
	   /// <param name="operand">�������</param>
	   /// <returns>����</returns>
	   Node* createOperandNode(double operand) {
		   //�������������� ����� � ������ � ���������� ��� � �������� ������ ����
		   return new Node(std::to_string(operand));
	   }

	   /// <summary>
	   /// ��������� �������� �� ����
	   /// </summary>
	   /// <param name="node">����</param>
	   /// <returns>������� �� ����</returns>
	   double getOperandValue(Node* node) {
		   //�������������� ������ � ����� ���� double
		   return std::stod(node->data);
	   }

	   /// <summary>
	   /// �������� ���� ��� ���������
	   /// </summary>
	   /// <param name="op">��������</param>
	   /// <param name="left">������ �� ����� �������</param>
	   /// <param name="right">������ �� ������ �������</param>
	   /// <returns>����</returns>
	   Node* createOperatorNode(const std::string& op, Node* left, Node* right) {
		   Node* node = new Node(op);
		   node->left = left;
		   node->right = right;
		   return node;
	   }

	   /// <summary>
	   /// ������������ ����������� ��������
	   /// </summary>
	   /// <param name="op">������� ��������</param>
	   /// <returns>������� ����������</returns>
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
       /// ����������� ��������� � ������ ��� ������������ ���������� ��������.
       /// </summary>
       /// <param name="expression">������ � ����������</param>
       /// <returns>������ ������</returns>
	   Node* parseExpression(const std::string& expression) {
		   std::stack<Node*> nodeStack; // ���� ��� �������� ����� ������ ���������
		   std::stack<char> opStack;    // ���� ��� �������� ���������� (+, -, *, /)
		   std::string operand;         // ������ ��� ����� ��������� (�����) �� ���������

		   for (size_t i = 0; i < expression.size(); ++i) {
			   char c = expression[i];

			   if (isspace(c)) { // ������� ��������
				   continue;
			   }
			   else if (isdigit(c) || c == '.') { // ���� �������� ��������
				   if (isdigit(c))
					   operand += c;
				   else
					   operand += ',';
			   }
			   else { // ���� ������ - �������� ��� ������
				   if (!operand.empty()) { // ���� ������� �� ������, ��������� ��� � ���� �����
					   nodeStack.push(createOperandNode(std::stod(operand)));
					   operand.clear();
				   }

				   if (c == '(') { // ���� ������ - ����������� ������, ��������� � � ���� ����������
					   opStack.push(c);
				   }
				   else if (c == ')') { // ���� ������ - ����������� ������, ��������� �������� �� ����������� ������
					   while (!opStack.empty() && opStack.top() != '(') {
						   // ��������� �������� � ������: �������� ��������, ������� ��� �� �����, ������� ���� ��������
						   char op = opStack.top();
						   opStack.pop();

						   if (nodeStack.size() < 2) {
							   // ���� ��������� ������������ ��� ��������, ������� ��������� �� ������
							   System::Windows::Forms::MessageBox::Show("������: ������������ ��������� ��� �������� " + gcnew String(1, op));
							   return nullptr;
						   }

						   Node* right = nodeStack.top();
						   nodeStack.pop();
						   Node* left = nodeStack.top();
						   nodeStack.pop();

						   nodeStack.push(createOperatorNode(std::string(1, op), left, right)); // ������� ���� �������� � ��������� � ���� �����
					   }
					   if (!opStack.empty() && opStack.top() == '(') {
						   opStack.pop(); // ������� ����������� ������ �� �����
					   }
					   else {
						   // ��� ��������������� ����������� ������, ������� ��������� �� ������
						   System::Windows::Forms::MessageBox::Show("������: �� ������� ����������� ������");
						   return nullptr;
					   }
				   }
				   else if (c == '+' || c == '-' || c == '*' || c == '/') { // ���� ������ - ��������, ��������� �������� � ����������� �� ����������
					   while (!opStack.empty() && opStack.top() != '(' && getPriority(opStack.top()) >= getPriority(c)) {
						   char op = opStack.top();
						   opStack.pop();

						   if (nodeStack.size() < 2) {
							   // ���� ��������� ������������ ��� ��������, ������� ��������� �� ������
							   System::Windows::Forms::MessageBox::Show("������: ������������ ��������� ��� �������� " + gcnew String(1, op));
							   return nullptr;
						   }

						   Node* right = nodeStack.top();
						   nodeStack.pop();
						   Node* left = nodeStack.top();
						   nodeStack.pop();

						   nodeStack.push(createOperatorNode(std::string(1, op), left, right)); // ������� ���� �������� � ��������� � ���� �����
					   }
					   opStack.push(c); // ��������� ������� �������� � ���� ����������
				   }
				   else {
					   // ����� ������ ������ ��������� ������������ � ���������, ������� ��������� �� ������
					   System::Windows::Forms::MessageBox::Show("������: ����������� ������");
					   return nullptr;
				   }
			   }
		   }

		   if (!operand.empty()) { // ���� ������� ��������� �������
			   nodeStack.push(createOperandNode(std::stod(operand)));
		   }

		   // ���������� ����������: ���������� ��������, ���� ���� �������� �� ��������
		   while (!opStack.empty()) {
			   char op = opStack.top();
			   opStack.pop();

			   if (nodeStack.size() < 2) {
				   // ���� ��������� ������������ ��� ��������, ������� ��������� �� ������
				   System::Windows::Forms::MessageBox::Show("������: ������������ ��������� ��� �������� " + gcnew String(1, op));
				   return nullptr;
			   }

			   Node* right = nodeStack.top();
			   nodeStack.pop();
			   Node* left = nodeStack.top();
			   nodeStack.pop();

			   nodeStack.push(createOperatorNode(std::string(1, op), left, right)); // ������� ���� �������� � ��������� � ���� �����
		   }

		   // �������� �� ������� ������ ����� � ����� �����
		   if (nodeStack.size() != 1) {
			   // ���� ���������� ����� �� ����� ������, ������� ��������� �� ������
			   System::Windows::Forms::MessageBox::Show("������ � ���������");
			   return nullptr;
		   }

		   return nodeStack.top(); // ���������� ������ ������
	   }

	   /// <summary>
	   /// ���������� ������� ����������
       /// <summary>
       /// ��������� �������������� �������� ����� ����� ����������.
       /// </summary>
       /// <param name="a">�������� ������ ����������</param>
       /// <param name="b">�������� ������ ����������</param>
       /// <param name="op">�������� ��� ���������� (+, -, *, /)</param>
       /// <returns>��������� ��������</returns>
	   double calculate(double a, double b, char op) {
		   switch (op) {
		   case '+': // ��������
			   return a + b;
		   case '-': // ���������
			   return a - b;
		   case '*': // ���������
			   return a * b;
		   case '/': // �������
			   if (b != 0) {
				   return a / b; // ���� �������� �� ����, ��������� �������
			   }
			   else {
				   System::Windows::Forms::MessageBox::Show("������: ������� �� ����"); // ����� ��������� �� ������ ������� �� ����
			   }
		   default: // ��������� ������������ ��������
			   System::Windows::Forms::MessageBox::Show("������: ������������ ��������"); // ����� ��������� �� ������ ��� ������������ ��������
			   return 0; // ���������� 0 � ������ ������������ ��������
		   }
	   }


	   /// <summary>
	   /// ��������� ���������� �������� ���������, ��������������� � ���� ������.
	   /// </summary>
	   /// <param name="root">������ �� �������� ���� ������ ���������</param>
	   /// <returns>��������� ����������</returns>
	   double evaluateExpressionTree(Node* root) {
		   if (root) {
			   // ���� ���� - ���� (�� ����� �������� �����), ���������� �������� �������� ����
			   if (!root->left && !root->right) {
				   return std::stod(root->data); // ����������� ������ � ����� � ���������� �� ��������
			   }
			   else {
				   // ���������� ��������� ����� � ������ ���������� � ��������� �������� ����� ����
				   double leftValue = evaluateExpressionTree(root->left);
				   double rightValue = evaluateExpressionTree(root->right);
				   return calculate(leftValue, rightValue, root->data[0]); // ��������� �������� ����� ������
			   }
		   }
		   return 0.0; // ���������� 0, ���� ���� �� ����������
	   }


	   /// <summary>
	   /// ���������� � ���� �������� ����������, ��������� �������������.
	   /// </summary>
	   /// <param name="variableValues">�������� ����������</param>
	   /// <param name="filename">�������� ����� ��� ������</param>
	   void writeVariablesToFile(const std::map<std::string, double>& variableValues, const std::string& filename) {
		   std::ofstream outputFile(selectedFilePath, std::ios::app); // ��������� ���� ��� ������

		   if (outputFile.is_open()) {
			   // ���������� �������� ���������� � ���� � ������� "����������=��������"
			   for (const auto& pair : variableValues) {
				   outputFile << pair.first << "=" << pair.second << "\n";
			   }
			   outputFile.close(); // ��������� ���� ����� ������
		   }
		   else {
			   // ���� �� ������� ������� ���� ��� ������, ������� ��������� �� ������
			   System::Windows::Forms::MessageBox::Show("������ �������� �����");
		   }
	   }


	   /// <summary>
	   /// ������� ��� ��������� ������� � ������ ���������� � ����
       /// <summary>
       /// ������������ ������� � ��������� ��������� ��� ������ �������, ��������� ��������� � ����.
       /// </summary>
       /// <param name="num">����� ������ (1 ��� 2)</param>
       /// <param name="root">������ ������ ��� ����������</param>
       /// <param name="expression">�������</param>
       /// <param name="variableValues">�������� ����������</param>
	   void processFormula(int num, Node* root, std::string expression, std::map<std::string, double> variableValues) {
		   // ��������� ��������� ��� ������ ������� � ������� ������ ���������
		   double result = evaluateExpressionTree(root);

		   // ����������� ������� ��� ���������� ������ � ����
		   fileMutex.lock();

		   // ��������� ���� ��� ������ ����������
		   std::ofstream outFile(selectedFilePath, std::ios::app);
		   if (outFile.is_open()) {
			   outFile << expression << "\n"; // ���������� ������� � ����
			   writeVariablesToFile(variableValues, selectedFilePath); // ���������� �������� ���������� � ����

			   try {
				   if (num == 1)
					   result1 = result; // ���������� ��������� � ���������� result1 ��� ������� ������
				   else
					   result2 = result; // ���������� ��������� � ���������� result2 ��� ������� ������

				   outFile << result << "\n"; // ���������� ��������� � ����
			   }
			   catch (const std::runtime_error& e) {
				   // ��������� ������ ��� ���������� ����������
				   System::Windows::Forms::MessageBox::Show("������");
			   }
			   outFile.close(); // ��������� ����
		   }
		   fileMutex.unlock(); // ����������� �������
	   }


	   /// <summary>
	   /// ��������� ���������� ������ �������.
	   /// </summary>
	   void PerformCalculation() {
		   setlocale(LC_ALL, "Russian"); // ������������� ������� ������ ��� ������ � ���������� �������

		   // �������� ��������� �� ���������� ���� �����
		   std::string expression = msclr::interop::marshal_as<std::string>(FormulaEntering->Text);

		   // ��������� ���������� ���������
		   if (isValidExpression(expression)) {
			   std::vector<std::string> variables = GetVariablesFromFormula(expression); // �������� ������ ���������� �� ���������

			   // ������ ������� ��� �������� �������� ����������
			   std::map<std::string, double> variableValues;

			   // �������� �������� ���������� �� ��������� ����� �����
			   for (size_t i = 0; i < variables.size(); ++i) {
				   TextBox^ textBox = dynamic_cast<TextBox^>(this->Controls[gcnew String(("txtVariable" + std::to_string(i)).c_str())]);
				   if (textBox != nullptr) {
					   double value;
					   if (Double::TryParse(textBox->Text, value)) {
						   variableValues[variables[i]] = value; // ��������� �������� ���������� � �������
					   }
					   else {
						   // ��������� ������: ������� ������������ �������� ����������
						   MessageBox::Show("������������ �������� ��� ���������� " + gcnew String(variables[i].c_str()));
						   return;
					   }
				   }
				   else {
					   // ��������� ������: ������� ���������� �� ������
					   MessageBox::Show("������� ���������� �� ������ ��� ���������� " + gcnew String(variables[i].c_str()));
					   return;
				   }
			   }

			   // ��������� ���� ��� ������ (���� selectedFilePath �������� ���� � �����)
			   std::ofstream outputFile(selectedFilePath, std::ios::app);

			   // �������� ���������� � ��������� �� �� �������� ��������
			   std::string substitutedExpression = SubstituteVariables(expression, variableValues);

			   // ������ ��������� � ������ ������ ���������
			   Node* root = parseExpression(substitutedExpression); // �����������, ��� ���� ������� ��� �������� ������ ���������

			   // ��������� ��������� ������� (������������, ��� processFormula ������������ ���������)
			   processFormula(1, root, expression, variableValues);

		   }
		   else {
			   // �������� ��� ������ � ���������
			   System::Windows::Forms::MessageBox::Show("������ � ���������2");
		   }
	   }


	   /// <summary>
	   /// ��������� ���������� ������ �������.
	   /// </summary>
	   void PerformCalculation2() {
		   setlocale(LC_ALL, "Russian"); // ������������� ������� ������ ��� ������ � ���������� �������

		   // �������� ��������� �� ���������� ���� �����
		   std::string expression = msclr::interop::marshal_as<std::string>(FormulaEntering2->Text);

		   // ��������� ���������� ���������
		   if (isValidExpression(expression)) {
			   std::vector<std::string> variables = GetVariablesFromFormula(expression); // �������� ������ ���������� �� ���������

			   // ������ ������� ��� �������� �������� ����������
			   std::map<std::string, double> variableValues;

			   // �������� �������� ���������� �� ��������� ����� �����
			   for (size_t i = 0; i < variables.size(); ++i) {
				   TextBox^ textBox = dynamic_cast<TextBox^>(this->Controls[gcnew String(("2txtVariable" + std::to_string(i)).c_str())]);
				   if (textBox != nullptr) {
					   double value;
					   if (Double::TryParse(textBox->Text, value)) {
						   variableValues[variables[i]] = value; // ��������� �������� ���������� � �������
					   }
					   else {
						   // ��������� ������: ������� ������������ �������� ����������
						   MessageBox::Show("������������ �������� ��� ���������� " + gcnew String(variables[i].c_str()));
						   return;
					   }
				   }
				   else {
					   // ��������� ������: ������� ���������� �� ������
					   MessageBox::Show("������� ���������� �� ������ ��� ���������� " + gcnew String(variables[i].c_str()));
					   return;
				   }
			   }

			   // ��������� ���� ��� ������ (�����������, ��� selectedFilePath �������� ���� � �����)
			   std::ofstream outputFile(selectedFilePath, std::ios::app);

			   // �������� ���������� � ��������� �� �� �������� ��������
			   std::string substitutedExpression = SubstituteVariables(expression, variableValues);

			   // ������ ��������� � ������ ������ ���������
			   Node* root = parseExpression(substitutedExpression); // ������������, ��� ���� ������� ��� �������� ������ ���������

			   // ��������� ��������� ������� (������������, ��� processFormula ������������ ���������)
			   processFormula(2, root, expression, variableValues);

		   }
		   else {
			   // �������� ��� ������ � ���������
			   System::Windows::Forms::MessageBox::Show("������ � ���������3");
		   }
	   }


	   /// <summary>
	   /// �������� ���������� � ������� �� �������� �������� � �������������� ��������������� �������� ����������.
	   /// </summary>
	   /// <param name="expression">�������� �������</param>
	   /// <param name="variableValues">�������� ����������</param>
	   /// <returns>������� � ���������� ����������� �� �� �������� ��������</returns>
	   std::string SubstituteVariables(const std::string& expression, const std::map<std::string, double>& variableValues) {
		   std::string substitutedExpression = expression; // �������� �������� ������� ��� ������ ����������

		   // ��� ������ ���������� �� ��������������� ��������
		   for (const auto& pair : variableValues) {
			   size_t pos = 0;
			   // ���� ���������� ������� � �������
			   while ((pos = substitutedExpression.find(pair.first, pos)) != std::string::npos) {
				   std::ostringstream oss;
				   oss.precision(15); // ������������� �������� ��� ��������� �������� ����������
				   oss << std::fixed << pair.second; // ����������� �������� ���������� � ������
				   substitutedExpression.replace(pos, pair.first.length(), oss.str()); // �������� ���������� �� �������� ��������
				   pos += oss.str().length(); // ��������� ������� ��� ������ ��������� ����������
			   }
		   }
		   return substitutedExpression; // ���������� ������� � ���������� ���������� ����������
	   }



	   /// <summary>
	   /// ���������� ������� ������� �� ������ "����������". ������� ��� ������ ��� ����������,
	   /// ������� �� ����������, ������� ���������� � ��������������� ��������� ���� � ������������� ������� �� �����.
	   /// </summary>
	   /// <param name="sender">������, �������������� �������</param>
	   /// <param name="e">��������� �������</param>
private: System::Void BtnCount_Click(System::Object^ sender, System::EventArgs^ e) {
	// �������� ���� ������� ��� ���������� ����������
	Thread^ thread1 = gcnew Thread(gcnew ThreadStart(this, &MainForm::PerformCalculation));
	Thread^ thread2 = gcnew Thread(gcnew ThreadStart(this, &MainForm::PerformCalculation2));

	// ������ �������
	thread1->Start();
	thread2->Start();

	// �������� ���������� ������ �������
	thread1->Join();
	thread2->Join();

	// �������� ��������� ����� ��� ������ ����������� ������� � ������� �������
	TextBox^ resultTextBox = gcnew TextBox();
	TextBox^ resultTextBox2 = gcnew TextBox();

	// ����� ���������� ��� ������� ������
	// �������� � ��������� textBox ��� ������ ���������� ������� ������
	resultTextBox->Size = System::Drawing::Size(120, 20);
	resultTextBox->Location = System::Drawing::Point(75, 377);
	resultTextBox->Text = result1.ToString("F5"); // result1 - ��������� ���������� ������� ������
	this->Controls->Add(resultTextBox);

	// ����� ���������� ��� ������� ������
	// �������� � ��������� textBox ��� ������ ���������� ������� ������
	resultTextBox2->Size = System::Drawing::Size(120, 20);
	resultTextBox2->Location = System::Drawing::Point(595, 377);
	resultTextBox2->Text = result2.ToString("F5"); // result2 - ��������� ���������� ������� ������
	this->Controls->Add(resultTextBox2);

	// ������������ ������ �� �����
	LoadFormulasFromFile(gcnew System::String(selectedFilePath.c_str()));
}


/// <summary>
/// ���������� ������� ������� �� ������ 1. ��������� ���������� ���������, ��������� ���������� � ��������� �������� ����� ����������.
/// </summary>
/// <param name="sender">������, �������������� �������</param>
/// <param name="e">��������� �������</param>
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	// �������������� ������ ��������� ������� � ������ C++
	std::string formula = msclr::interop::marshal_as<std::string>(FormulaEntering->Text);

	// �������� ���������� ���������
	if (isValidExpression(formula)) {
		// ���������� ���������� �� �������
		std::vector<std::string> variables = GetVariablesFromFormula(formula);

		// ������� ���������� ��������� ��� ����� ����������
		ClearVariableControls();

		// �������� ����� ��������� ��� ����� ���������� �� ������ ����������� ����������
		CreateVariableControls(variables);
	}
	else {
		// ����� ��������� ������������ ��� ������ � ���������
		System::Windows::Forms::MessageBox::Show("������ � ���������");
	}
}


/// <summary>
/// ���������� ������� ������� �� ������ 2. ��������� ���������� ���������, ��������� ���������� � ��������� �������� ����� ����������.
/// </summary>
/// <param name="sender">������, �������������� �������</param>
/// <param name="e">��������� �������</param>
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	// �������������� ������ ��������� ������� � ������ C++
	std::string formula = msclr::interop::marshal_as<std::string>(FormulaEntering2->Text);

	// �������� ���������� ���������
	if (isValidExpression(formula)) {
		// ���������� ���������� �� �������
		std::vector<std::string> variables = GetVariablesFromFormula(formula);

		// ������� ���������� ��������� ��� ����� ����������
		ClearVariableControls2();

		// �������� ����� ��������� ��� ����� ���������� �� ������ ����������� ����������
		CreateVariableControls2(variables);
	}
	else {
		// ����� ��������� ������������ ��� ������ � ���������
		System::Windows::Forms::MessageBox::Show("������ � ���������");
	}
}


	   /// <summary>
       /// �������� ��������� ����� ��� ����� �������� ���������� ��������� ������� ������
       /// </summary>
       /// <param name="variables">������ ����������, ����������� �� �������</param>
	   void CreateVariableControls2(const std::vector<std::string>& variables) {
		   int yPos = 150;    // ��������� ������� �� ��������� ��� ���������� ��������� ����������
		   int tabIndex = 1;  // ��������� ������ ��� ������������ ����� ���������� ���������� (Tab Order)

		   // ������ �� ������ ���������� ��� �������� ��������� ����� � ��������� ����� �����
		   for (size_t i = 0; i < variables.size(); ++i) {
			   Label^ label = gcnew Label();    // �������� ����� ��� ����������� ����� ����������
			   label->Text = gcnew String(variables[i].c_str());  // ��������� ������ �����
			   label->Location = Point(510, yPos);    // ������� ������� ����� �� ����������� � ���������
			   label->AutoSize = true;   // ��������� ��������������� ������� �����
			   label->Name = "2label" + i.ToString();  // ������� ����� �����

			   TextBox^ textBox = gcnew TextBox(); // �������� ���������� ���� ��� ����� �������� ����������
			   textBox->Name = "2txtVariable" + i.ToString(); // ��������� ����� ���������� ����
			   textBox->Location = Point(530, yPos);   // ������� ������� ���������� ���� �� ����������� � ���������
			   textBox->TabIndex = tabIndex++; // ��������� ������� ������������ ��� ����������������� �������������
			   textBox->Size = Drawing::Size(30, 20);   // ��������� ������� ���������� ����

			   // ���������� ����� � ���������� ���� � ��������� ��������� ���������� �����
			   this->Controls->Add(label);
			   this->Controls->Add(textBox);

			   yPos += 30; // ����������� �� ��������� ������� �� ��������� ��� ���������� ��������
		   }
	   }


	   /// <summary>
	   /// �������� ���������� ���� ��� ����� ���������� ������� ������
	   /// </summary>
	   void ClearVariableControls2() {
		   // �������� ������ ��������� ����������, ������� ����� �������
		   System::Collections::Generic::List<Control^>^ controlsToRemove = gcnew System::Collections::Generic::List<Control^>();

		   // ����� � ���������� ��������� ���������� ��� ��������
		   for each (Control ^ control in this->Controls) {
			   // �������� �������� ��������, ������� �������������� ������� (� �������, ������������� �� "2txtVariable" ��� "2label")
			   if (control->Name->StartsWith("2txtVariable") || control->Name->StartsWith("2label")) {
				   controlsToRemove->Add(control); // ���������� ��������� ���������� � ������ ��� ��������
			   }
		   }

		   // �������� ��������� ���������� �� ������������� ����������
		   for each (Control ^ control in controlsToRemove) {
			   this->Controls->Remove(control); // �������� ��������� �� ������ ���������
		   }
	   }

	   // ���������� ��������� ���������� �������� � ������ ������ (������ �����)
private: System::Void ChooseFormula2_SelectedItemChanged(System::Object^ sender, System::EventArgs^ e) {
	try {
		// ��������� ��������� ������� �� ������ ������ ������� ������
		System::String^ selectedFormula = ChooseFormula2->SelectedItem->ToString();

		// ����������� ��������� ������� � ��������������� ���� �����
		FormulaEntering2->Text = selectedFormula;

		// �������������� ��������� ������� � ������ C++
		std::string formula = msclr::interop::marshal_as<std::string>(selectedFormula);

		// ��������� ���������� �� ��������� �������
		std::vector<std::string> variables = GetVariablesFromFormula(formula);

		// ������� ����������� ������ ��������� ���������� ��� ���������� ������� ������
		ClearVariableControls2();

		// �������� ��������� ���������� ��� ���������� �� ������ ������ ����������
		CreateVariableControls2(variables);
	}
	catch (Exception^ ex) {
		// ��������� ��������� ���������� � ����������� ��������� �� ������
		MessageBox::Show("������ ��� ������ �������: " + ex->Message, "������");
	}
}

// ���������� ������� ������� ������ "������� ����� ����"
private: System::Void BtnNewFile_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		// ������ � ������������ ����� � ���� ��� ������ ����� ����� ������ ����������
		SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
		saveFileDialog1->Filter = "Text Files (*.txt)|*.txt"; // ������ ��� ������ .txt
		saveFileDialog1->Title = "Save a Text File"; // ��������� ������� ����������

		// ���� ������������ ������ ���� � ���������� ����������
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			String^ filePath = saveFileDialog1->FileName; // ��������� ���� � ���������� �����

			// �������� ������ .txt ����� �� ���������� ����
			std::ofstream file(msclr::interop::marshal_as<std::string>(filePath));
			file.close(); // �������� �����
			selectedFilePath = msclr::interop::marshal_as<std::string>(filePath); // ���������� ���� ��� ������������ �������������
			LoadFormulasFromFile(filePath); // �������� ������ �� ���������� �����

			// ����������� ��������� �� �������� �������� �����
			MessageBox::Show("���� ������� ������.");
		}
	}
	catch (Exception^ ex) {
		// ��������� ��������� ���������� � ����������� ��������� �� ������
		MessageBox::Show("������ ��� �������� �����: " + ex->Message, "������");
	}
}
};

}
