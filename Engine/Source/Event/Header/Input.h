#ifndef OWL_INPUT
#define OWL_INPUT

namespace owl
{
	class Input
	{
	public:

		friend class Application;

	protected:
		Input() {};

		// Deletes copy constructor and assigment operator
		Input(const Input&) = delete;
		Input operator=(const Input&) = delete;

		// Gets the class's static reference
		static Input& GetInstance() { static Input s_Instance; return s_Instance; }

	private:
		void OWL_API PollEvents();
	};
}

#endif // !OWL_INPUT
