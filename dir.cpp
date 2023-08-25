#include <filesystem>
#include <iomanip>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
  namespace fs = std::filesystem;
  using namespace std;

  if (argc != 2)
  {
    cerr << "Usage: " << argv[0] << " <path>\n";
    return 1;
  }

  fs::path const base = argv[1];
  for (auto const& entry : 
    fs::recursive_directory_iterator(
      base,
      fs::directory_options::skip_permission_denied
    )
  )
  {
    auto const p = quoted(entry.path().native());

    if (fs::is_symlink(entry))
      cout << "LINK: " << p << '\n';
    else if (fs::is_regular_file(entry))
      cout << "FILE: " << fs::file_size(entry) << ' ' << p << '\n';
    else if (fs::is_directory(entry))
      cout << "DIR: " << p << '\n';
    else
      cout << "OTHER: " << p << '\n';
  }
}
