#include "Core/Network/TCPClient.h"

TCPClient::TCPClient()
{
	Connected = false;
	BytesSent = 0;
	Socket = nullptr;
	RecreateSocket();
	UE_LOG(LogTemp, Warning, TEXT("Socket created"));
}

TCPClient::~TCPClient()
{
	Close();	
	delete Socket;
}

bool TCPClient::Connect(FIPv4Address IP, int32 Port, int32 Timeout)
{
	if (Socket == nullptr) return false;
	auto Address = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	Address->SetIp(IP.Value);
	Address->SetPort(Port);
	Connected = Socket->Connect(*Address);
	return Connected;
}

bool TCPClient::Close()
{
	UE_LOG(LogTemp, Warning, TEXT("Socket closed"));
	return Socket->Close();
}

int32 TCPClient::Write(unsigned char* Data, int32 Size)
{
	if (Socket->GetConnectionState() == ESocketConnectionState::SCS_NotConnected) return 0;
	if (Size < 0 || Data == nullptr) return 0;
	bool IsSent = Socket->Send((uint8*)Data, Size, BytesSent);
	if (IsSent) return BytesSent;
	return -1;
}

TArray<unsigned char> TCPClient::Read(int32 Size, int32 Timeout)
{
	if (Socket->GetConnectionState() == ESocketConnectionState::SCS_NotConnected) return TArray<unsigned char>();
	if (Socket->GetConnectionState() == ESocketConnectionState::SCS_ConnectionError) return TArray<unsigned char>();
	int32 BytesToReceive = Size;
	uint8* Data = new uint8[Size];
	TArray<unsigned char> Temp;
	Temp.Reserve(Size);
	do
	{
		int32 BytesRead = -1;
		bool Receive = Socket->Recv(Data, BytesToReceive, BytesRead);
		if (Receive)
		{
			for (int32 i = 0; i < BytesRead; i++) Temp.Add(Data[i]);
		}
		else
		{
			break;
		}
		BytesToReceive -= BytesRead;
	} while (BytesToReceive != 0);
	delete[] Data;
	return Temp;
}

bool TCPClient::IsConnected()
{
	return Connected;
}

void TCPClient::RecreateSocket()
{
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("NetworkGameSocket"), false);
}
