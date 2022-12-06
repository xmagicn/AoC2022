#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <stack>

int Year22Day1Part1( const std::string& Filename )
{
	std::ifstream myfile;
	myfile.open( Filename );

	int CurrentSum = 0;
	int CurrentMax = 0;

	while ( myfile.good() )
	{
		char line[256];
		myfile.getline( line, 256 );
		std::string Line( line );

		if ( Line.compare( "" ) )
		{
			CurrentSum += stoi( Line );
		}
		else
		{
			if ( CurrentSum > CurrentMax )
			{
				CurrentMax = CurrentSum;
			}
			CurrentSum = 0;
		}
	}

	myfile.close();

	return CurrentMax;
}

int Year22Day1Part2( const std::string& Filename )
{
	std::ifstream myfile;
	myfile.open( Filename );

	int CurrentSum = 0;

	std::vector<int> TopFour;

	while ( myfile.good() )
	{
		char line[256];
		myfile.getline( line, 256 );
		std::string Line( line );

		if ( Line.compare( "" ) )
		{
			CurrentSum += stoi( Line );
		}
		else
		{
			if ( TopFour.size() < 4 )
			{
				TopFour.push_back( CurrentSum );
			}
			else
			{
				TopFour[0] = CurrentSum;
				std::sort( TopFour.begin(), TopFour.end() );
			}
			CurrentSum = 0;
		}
	}

	if ( TopFour.size() < 4 )
	{
		TopFour.push_back( CurrentSum );
	}
	else
	{
		TopFour[0] = CurrentSum;
	}
	std::sort( TopFour.begin(), TopFour.end() );

	myfile.close();

	return TopFour[1] + TopFour[2] + TopFour[3];
}

int Day2Part1( const std::string& Filename )
{
	return 0;
}

int Day2Part2( const std::string& Filename )
{
	return 0;
}

int Day3Part1( const std::string& Filename )
{
	std::ifstream myfile;
	myfile.open( Filename );

	std::vector<char> Letters;
	while ( myfile.good() )
	{
		char line[256];
		myfile.getline( line, 256 );
		std::string Line( line );

		if ( Line.size() <= 0 )
		{
			continue;
		}

		std::string Left, Right;
		Left = Line.substr( 0, Line.size() / 2 );
		Right = Line.substr( Line.size() / 2, Line.size() - 1 );
	
		bool bFoundLetter = false;
		for ( size_t Idx = 0; Idx < Left.size(); ++Idx )
		{
			if ( std::count( Right.begin(), Right.end(), Left[Idx] ) )
			{
				Letters.push_back( Left[Idx] );
				bFoundLetter = true;
				break;
			}
		}

		if ( !bFoundLetter )
			std::cout << "bad" << std::endl;
	}

	int OutScore = 0;
	const int ASCIILowerDiff = 96;
	const int ASCIIUpperDiff = 38;
	for ( char Letter : Letters )
	{
		int Diff = isupper( Letter ) ? ASCIIUpperDiff : ASCIILowerDiff;
		int Score = static_cast< int >( Letter ) - Diff;
		OutScore += Score;
	}

	myfile.close();

	return OutScore;
}

int Day3Part2( const std::string& Filename )
{
	std::ifstream myfile;
	myfile.open( Filename );

	std::vector<char> Letters;
	while ( myfile.good() )
	{
		std::vector<std::string> Lines;

		char line[256];
		myfile.getline( line, 256 );
		Lines.push_back(std::string( line ));
		myfile.getline( line, 256 );
		Lines.push_back( std::string( line ) );
		myfile.getline( line, 256 );
		Lines.push_back( std::string( line ) );

		std::vector<char> Candidates;
		for ( size_t Idx = 0; Idx < Lines[0].size(); ++Idx )
		{
			if ( std::count( Lines[1].begin(), Lines[1].end(), Lines[0][Idx] ) )
			{
				Candidates.push_back( Lines[0][Idx] );
			}
		}

		if ( Candidates.size() == 0 )
			std::cout << "bad" << std::endl;

		bool bFoundLetter = false;
		for ( size_t Idx = 0; Idx < Lines[2].size(); ++Idx )
		{
			if ( std::count( Candidates.begin(), Candidates.end(), Lines[2][Idx] ) )
			{
				bFoundLetter = true;
				Letters.push_back( Lines[2][Idx] );
				break;
			}
		}

		if ( !bFoundLetter )
			std::cout << "bad" << std::endl;
	}

	int OutScore = 0;
	const int ASCIILowerDiff = 96;
	const int ASCIIUpperDiff = 38;
	for ( char Letter : Letters )
	{
		int Diff = isupper( Letter ) ? ASCIIUpperDiff : ASCIILowerDiff;
		int Score = static_cast< int >( Letter ) - Diff;
		OutScore += Score;
	}

	myfile.close();

	return OutScore;
}

struct ElfAssignment
{
	ElfAssignment( const std::string& InString )
	{
		Populate( InString );
	}

	void Populate( const std::string& InString )
	{
		auto start = 0U;
		auto end = InString.find( '-' );
		StartID = stoi( InString.substr( start, end ) );
		EndID = stoi( InString.substr( end + 1, std::string::npos ) );
	}

	bool DoesContain( const ElfAssignment& Other ) const
	{
		return StartID <= Other.StartID && EndID >= Other.EndID;;
	}

	bool DoesOverlap( const ElfAssignment& Other ) const
	{
		return !(EndID < Other.StartID || Other.EndID < StartID) || DoesContain(Other) || Other.DoesContain(*this);
	}

	int StartID = 0;
	int EndID = 0;
};

int Day4Part1( const std::string& Filename )
{
	std::ifstream myfile;
	myfile.open( Filename );

	int ContainedSum = 0;
	while ( myfile.good() )
	{
		char line[256];
		myfile.getline( line, 256 );
		std::string Line( line );

		auto start = 0U;
		auto end = Line.find( ',' );
		ElfAssignment Elf1( Line.substr( start, end ) );
		ElfAssignment Elf2( Line.substr( end + 1, std::string::npos ) );

		if ( Elf1.DoesContain(Elf2) || Elf2.DoesContain(Elf1) )
		{
			++ContainedSum;
		}
	}

	myfile.close();

	return ContainedSum;
}

int Day4Part2( const std::string& Filename )
{
	std::ifstream myfile;
	myfile.open( Filename );

	int OverlappedSum = 0;
	while ( myfile.good() )
	{
		char line[256];
		myfile.getline( line, 256 );
		std::string Line( line );

		auto start = 0U;
		auto end = Line.find( ',' );
		ElfAssignment Elf1( Line.substr( start, end ) );
		ElfAssignment Elf2( Line.substr( end + 1, std::string::npos ) );

		if ( Elf1.DoesOverlap( Elf2 ) )
		{
			++OverlappedSum;
		}
	}

	myfile.close();

	return OverlappedSum;
}

struct LoadingDock
{
	std::vector<std::stack<char>> Stacks;

	std::string GetTopCrates() const
	{
		std::string CrateSum;
		for ( const std::stack<char>& Stack : Stacks )
		{
			CrateSum += Stack.top();
		}
		return CrateSum;
	}
};

void ReadDay5Line( const std::string& Line, int& OutSrc, int& OutDest, int& OutCt )
{
	//move 1 from 2 to 1
	std::string MutLine = Line.substr( 5, std::string::npos);
	auto start = 0U;
	auto end = Line.find( " ", 6 );
	OutCt = stoi(Line.substr( 5, end - 5 ));
	
	start = end - 5;
	MutLine = Line.substr( end + 6, std::string::npos );
	end = MutLine.find( " " );
	OutSrc = stoi( MutLine.substr( 0, end ) );
	OutSrc--;

	start = end + 4;
	MutLine = MutLine.substr( start, std::string::npos );
	OutDest = stoi( MutLine );
	OutDest--;
}

std::string Day5Part1( const std::string& Filename, int NumDockLines, const LoadingDock& Input )
{
	LoadingDock MutDock = Input;

	std::ifstream myfile;
	myfile.open( Filename );

	for ( int Ct = 0; Ct < NumDockLines; ++Ct )
	{
		char line[256];
		myfile.getline( line, 256 );
	}

	while ( myfile.good() )
	{
		char line[256];
		myfile.getline( line, 256 );
		std::string Line( line );

		int Src, Dst, Ct;
		ReadDay5Line( Line, Src, Dst, Ct );

		for ( size_t Idx = 0; Idx < Ct; ++Idx )
		{
			char Item = MutDock.Stacks[Src].top();
			MutDock.Stacks[Src].pop();
			MutDock.Stacks[Dst].push( Item );
		}
	}

	myfile.close();

	return MutDock.GetTopCrates();
}

std::string Day5Part2( const std::string& Filename, int NumDockLines, const LoadingDock& Input )
{
	LoadingDock MutDock = Input;

	std::ifstream myfile;
	myfile.open( Filename );

	for ( int Ct = 0; Ct < NumDockLines; ++Ct )
	{
		char line[256];
		myfile.getline( line, 256 );
	}

	while ( myfile.good() )
	{
		char line[256];
		myfile.getline( line, 256 );
		std::string Line( line );

		int Src, Dst, Ct;
		ReadDay5Line( Line, Src, Dst, Ct );

		std::stack<char> Crane;
		for ( size_t Idx = 0; Idx < Ct; ++Idx )
		{
			Crane.push(MutDock.Stacks[Src].top());
			MutDock.Stacks[Src].pop();
		}		
		while ( Crane.size() > 0 )
		{
			MutDock.Stacks[Dst].push( Crane.top() );
			Crane.pop();
		}
	}

	myfile.close();

	return MutDock.GetTopCrates();
}

bool AreCharactersUnique( const std::string& InString )
{
	for ( char Curr : InString )
	{
		if ( std::count( InString.begin(), InString.end(), Curr ) > 1 )
		{
			return false;
		}
	}

	return true;
}

int Day6Part1( const std::string& Filename )
{
	std::ifstream myfile;
	myfile.open( Filename );

	int Answer = 0;
	while ( myfile.good() )
	{
		char line[2048];
		myfile.getline( line, 2048 );
		std::string Line( line );

		if ( Line.size() < 4 )
		{
			continue;
		}

		if ( Line[0] != Line[1]
			&& Line[0] != Line[2]
			&& Line[0] != Line[3]
			&& Line[1] != Line[2]
			&& Line[1] != Line[3]
			&& Line[2] != Line[3]
			)
		{
			Answer = 3;
			continue;
		}

		for ( int Idx = 4; Idx < Line.size(); ++Idx )
		{
			if ( AreCharactersUnique( Line.substr( Idx - 4, 4 ) ) )
			{
				Answer = Idx;
				break;
			}
		}
	}

	myfile.close();

	return Answer;
}

int Day6Part2( const std::string& Filename )
{
	std::ifstream myfile;
	myfile.open( Filename );

	int Answer = 0;
	while ( myfile.good() )
	{
		char line[4096];
		myfile.getline( line, 4096 );
		std::string Line( line );

		if ( Line.size() < 14 )
		{
			continue;
		}

		for ( int Idx = 14; Idx <= Line.size(); ++Idx )
		{
			if ( AreCharactersUnique( Line.substr( Idx - 14, 14 ) ) )
			{
				Answer = Idx;
				break;
			}
		}
	}

	myfile.close();

	return Answer;
}

int Day7Part1( const std::string& Filename )
{
	std::ifstream myfile;
	myfile.open( Filename );

	int Answer = 0;
	while ( myfile.good() )
	{
		char line[4096];
		myfile.getline( line, 4096 );
		std::string Line( line );
	}

	myfile.close();

	return 0;
}

int Day7Part2( const std::string& Filename )
{
	std::ifstream myfile;
	myfile.open( Filename );

	int Answer = 0;
	while ( myfile.good() )
	{
		char line[4096];
		myfile.getline( line, 4096 );
		std::string Line( line );
	}

	myfile.close();

	return 0;
}

int main()
{
	/*
	std::string Day1Sample( "C:\\Users\\N8\\Desktop\\AdventOfCode\\2022\\Day1Sample.txt" );
	std::string Day1Input( "C:\\Users\\N8\\Desktop\\AdventOfCode\\2022\\Day1Input.txt" );
	std::cout << "Day1Part1Sample: " << Year22Day1Part1( Day1Sample ) << std::endl;
	std::cout << "Day1Part1: " << Year22Day1Part1( Day1Input ) << std::endl
	std::cout << "Day1Part2Sample: " << Year22Day1Part2( Day1Sample ) << std::endl;
	std::cout << "Day1Part2: " << Year22Day1Part2( Day1Input ) << std::endl;



	std::string Day2Sample( "C:\\Users\\N8\\Desktop\\AdventOfCode\\2022\\Day1Sample.txt" );
	std::string Day2Input( "C:\\Users\\N8\\Desktop\\AdventOfCode\\2022\\Day1Input.txt" );
	std::cout << "Day2Part1Sample: " << Day2Part1( Day2Sample ) << std::endl;
	std::cout << "Day2Part1: " << Day2Part1( Day2Input ) << std::endl;
	std::cout << "Day2Part2Sample: " << Day2Part2( Day2Sample ) << std::endl;
	std::cout << "Day2Part2: " << Day2Part2( Day2Input ) << std::endl;



	std::string Day3Sample( "C:\\Users\\N8\\Desktop\\AdventOfCode\\2022\\Day3Sample.txt" );
	std::string Day3Input( "C:\\Users\\N8\\Desktop\\AdventOfCode\\2022\\Day3Input.txt" );
	std::cout << "Day3Part1Sample: " << Day3Part1( Day3Sample ) << std::endl;
	std::cout << "Day3Part1: " << Day3Part1( Day3Input ) << std::endl;
	std::cout << "Day3Part2Sample: " << Day3Part2( Day3Sample ) << std::endl;
	std::cout << "Day3Part2: " << Day3Part2( Day3Input ) << std::endl;



	std::string Day4Sample( "C:\\Users\\N8\\Desktop\\AdventOfCode\\2022\\Day4Sample.txt" );
	std::string Day4Input( "C:\\Users\\N8\\Desktop\\AdventOfCode\\2022\\Day4Input.txt" );
	std::cout << "Day4Part1Sample: " << Day4Part1( Day4Sample ) << std::endl;
	std::cout << "Day4Part1: " << Day4Part1( Day4Input ) << std::endl;
	std::cout << "Day4Part2Sample: " << Day4Part2( Day4Sample ) << std::endl;
	std::cout << "Day4Part2: " << Day4Part2( Day4Input ) << std::endl;


	LoadingDock SampleStacks;
	{
		std::stack<char> Stack0;
		Stack0.push( 'z' );
		Stack0.push( 'n' );
		std::stack<char> Stack1;
		Stack1.push( 'm' );
		Stack1.push( 'c' );
		Stack1.push( 'd' );
		std::stack<char> Stack2;
		Stack2.push( 'p' );
		SampleStacks.Stacks.push_back( Stack0 );
		SampleStacks.Stacks.push_back( Stack1 );
		SampleStacks.Stacks.push_back( Stack2 );
	}

	LoadingDock InputStacks;
	{
		std::stack<char> Stack0;
		Stack0.push( 's' );
		Stack0.push( 'c' );
		Stack0.push( 'v' );
		Stack0.push( 'n' );
		std::stack<char> Stack1;
		Stack1.push( 'z' );
		Stack1.push( 'm' );
		Stack1.push( 'j' );
		Stack1.push( 'h' );
		Stack1.push( 'n' );
		Stack1.push( 's' );
		std::stack<char> Stack2;
		Stack2.push( 'm' );
		Stack2.push( 'c' );
		Stack2.push( 't' );
		Stack2.push( 'g' );
		Stack2.push( 'j' );
		Stack2.push( 'n' );
		Stack2.push( 'd' );
		std::stack<char> Stack3;
		Stack3.push( 't' );
		Stack3.push( 'd' );
		Stack3.push( 'f' );
		Stack3.push( 'j' );
		Stack3.push( 'w' );
		Stack3.push( 'r' );
		Stack3.push( 'm' );
		std::stack<char> Stack4;
		Stack4.push( 'p' );
		Stack4.push( 'f' );
		Stack4.push( 'h' );
		std::stack<char> Stack5;
		Stack5.push( 'c' );
		Stack5.push( 't' );
		Stack5.push( 'z' );
		Stack5.push( 'h' );
		Stack5.push( 'j' );
		std::stack<char> Stack6;
		Stack6.push( 'd' );
		Stack6.push( 'p' );
		Stack6.push( 'r' );
		Stack6.push( 'q' );
		Stack6.push( 'f' );
		Stack6.push( 's' );
		Stack6.push( 'l' );
		Stack6.push( 'z' );
		std::stack<char> Stack7;
		Stack7.push( 'c' );
		Stack7.push( 's' );
		Stack7.push( 'l' );
		Stack7.push( 'h' );
		Stack7.push( 'd' );
		Stack7.push( 'f' );
		Stack7.push( 'p' );
		Stack7.push( 'w' );
		std::stack<char> Stack8;
		Stack8.push( 'd' );
		Stack8.push( 's' );
		Stack8.push( 'm' );
		Stack8.push( 'p' );
		Stack8.push( 'f' );
		Stack8.push( 'n' );
		Stack8.push( 'g' );
		Stack8.push( 'z' );
		InputStacks.Stacks.push_back( Stack0 );
		InputStacks.Stacks.push_back( Stack1 );
		InputStacks.Stacks.push_back( Stack2 );
		InputStacks.Stacks.push_back( Stack3 );
		InputStacks.Stacks.push_back( Stack4 );
		InputStacks.Stacks.push_back( Stack5 );
		InputStacks.Stacks.push_back( Stack6 );
		InputStacks.Stacks.push_back( Stack7 );
		InputStacks.Stacks.push_back( Stack8 );
	}

	std::string Day5Sample( "C:\\Users\\N8\\Desktop\\AdventOfCode\\2022\\Day5Sample.txt" );
	std::string Day5Input( "C:\\Users\\N8\\Desktop\\AdventOfCode\\2022\\Day5Input.txt" );
	std::cout << "Day5Part1Sample: " << Day5Part1( Day5Sample, 5, SampleStacks ) << std::endl;
	std::cout << "Day5Part1: " << Day5Part1( Day5Input, 10, InputStacks ) << std::endl;
	std::cout << "Day5Part2Sample: " << Day5Part2( Day5Sample, 5, SampleStacks ) << std::endl;
	std::cout << "Day5Part2: " << Day5Part2( Day5Input, 10, InputStacks ) << std::endl;



	std::string Day6Sample( "C:\\Users\\N8\\Desktop\\AdventOfCode\\2022\\Day6Sample.txt" );
	std::string Day6Input( "C:\\Users\\N8\\Desktop\\AdventOfCode\\2022\\Day6Input.txt" );
	std::cout << "Day6Part1Sample: " << Day6Part1( Day6Sample ) << std::endl;
	std::cout << "Day6Part1: " << Day6Part1( Day6Input ) << std::endl;
	std::cout << "Day6Part2Sample: " << Day6Part2( Day6Sample ) << std::endl;
	std::cout << "Day6Part2: " << Day6Part2( Day6Input ) << std::endl;
	//*/

	//*
	std::string Day7Sample( "C:\\Users\\N8\\Desktop\\AdventOfCode\\2022\\Day7Sample.txt" );
	std::string Day7Input( "C:\\Users\\N8\\Desktop\\AdventOfCode\\2022\\Day7Input.txt" );
	std::cout << "Day7Part1Sample: " << Day7Part1( Day7Sample ) << std::endl;
	std::cout << "Day7Part1: " << Day7Part1( Day7Input ) << std::endl;
	std::cout << "Day7Part2Sample: " << Day7Part2( Day7Sample ) << std::endl;
	std::cout << "Day7Part2: " << Day7Part2( Day7Input ) << std::endl;
	//*/

	std::cin.get();

	return 0;
}