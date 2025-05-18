import { useState, useEffect } from 'react';
import { PieChart, Pie, Cell, ResponsiveContainer, Legend, Tooltip } from 'recharts';
import { BarChart, Bar, XAxis, YAxis, CartesianGrid } from 'recharts';
import { Trash2, Edit, Plus, User, UserCog, Save, Upload, Download } from 'lucide-react';


// Initial polls data
const initialPolls = [
  {
    id: 1,
    title: "Який вид транспорту ви використовуєте найчастіше?",
    options: [
      { id: 1, text: "Автомобіль", votes: 45 },
      { id: 2, text: "Громадський транспорт", votes: 30 },
      { id: 3, text: "Велосипед", votes: 15 },
      { id: 4, text: "Ходжу пішки", votes: 10 }
    ]
  },
  {
    id: 2,
    title: "Скільки часу ви проводите в інтернеті щодня?",
    options: [
      { id: 1, text: "Менше 1 години", votes: 10 },
      { id: 2, text: "1-3 години", votes: 25 },
      { id: 3, text: "3-5 годин", votes: 40 },
      { id: 4, text: "Більше 5 годин", votes: 25 }
    ]
  },
  {
    id: 3,
    title: "Як часто ви займаєтесь спортом?",
    options: [
      { id: 1, text: "Щодня", votes: 20 },
      { id: 2, text: "2-3 рази на тиждень", votes: 35 },
      { id: 3, text: "Кілька разів на місяць", votes: 25 },
      { id: 4, text: "Рідко або ніколи", votes: 20 }
    ]
  }
];

// Colors for charts
const COLORS = ['#0088FE', '#00C49F', '#FFBB28', '#FF8042', '#8884D8', '#82CA9D'];

export default function App() {
  const [polls, setPolls] = useState([]);
  const [activeMode, setActiveMode] = useState('user'); // 'user' or 'admin'
  const [selectedPoll, setSelectedPoll] = useState(null);
  const [selectedOption, setSelectedOption] = useState(null);
  const [showSubmitMessage, setShowSubmitMessage] = useState(false);
  const [showEditForm, setShowEditForm] = useState(false);
  const [editingPoll, setEditingPoll] = useState(null);
  const [showPollResults, setShowPollResults] = useState(false);
  const [resultsPoll, setResultsPoll] = useState(null);

  // Load polls from localStorage on mount
  useEffect(() => {
    const savedPolls = localStorage.getItem('polls');
    if (savedPolls) {
      setPolls(JSON.parse(savedPolls));
    } else {
      // Use initial polls as fallback
      setPolls(initialPolls);
      localStorage.setItem('polls', JSON.stringify(initialPolls));
    }
  }, []);

  // Save polls to localStorage whenever they change
  useEffect(() => {
    if (polls.length > 0) {
      localStorage.setItem('polls', JSON.stringify(polls));
    }
  }, [polls]);

  // Export polls to JSON file
  const exportPolls = () => {
    const dataStr = JSON.stringify(polls, null, 2);
    const dataUri = 'data:application/json;charset=utf-8,'+ encodeURIComponent(dataStr);
    
    const exportFileDefaultName = 'polls.json';
    
    const linkElement = document.createElement('a');
    linkElement.setAttribute('href', dataUri);
    linkElement.setAttribute('download', exportFileDefaultName);
    linkElement.click();
  };

  // Import polls from JSON file
  const importPolls = (event) => {
    const file = event.target.files[0];
    if (!file) return;

    const reader = new FileReader();
    reader.onload = (e) => {
      try {
        const importedPolls = JSON.parse(e.target.result);
        if (Array.isArray(importedPolls)) {
          setPolls(importedPolls);
          localStorage.setItem('polls', JSON.stringify(importedPolls));
          alert('Опитування успішно імпортовано!');
        } else {
          alert('Невірний формат файлу. Файл повинен містити масив опитувань.');
        }
      } catch (error) {
        alert('Помилка при імпорті файлу: ' + error.message);
      }
    };
    reader.readAsText(file);
    
    // Reset file input
    event.target.value = null;
  };

  // Submit handler for voting
  const handleSubmit = (e) => {
    if (selectedOption !== null) {
      const updatedPolls = polls.map(poll => {
        if (poll.id === selectedPoll.id) {
          const updatedOptions = poll.options.map(option => {
            if (option.id === selectedOption) {
              return { ...option, votes: option.votes + 1 };
            }
            return option;
          });
          return { ...poll, options: updatedOptions };
        }
        return poll;
      });
      
      setPolls(updatedPolls);
      setShowSubmitMessage(true);
      
      setTimeout(() => {
        setShowSubmitMessage(false);
        setSelectedPoll(null);
        setSelectedOption(null);
      }, 2000);
    }
  };

  // Delete poll handler
  const handleDeletePoll = (pollId, e) => {
    e.stopPropagation();
    setPolls(polls.filter(poll => poll.id !== pollId));
  };

  // Edit poll handler
  const handleEditPoll = (poll, e) => {
    e && e.stopPropagation();
    setEditingPoll({...poll});
    setShowEditForm(true);
  };

  // Save edited poll
  const handleSavePoll = (e) => {
    if (editingPoll) {
      if (editingPoll.id) {
        // Update existing poll
        setPolls(polls.map(poll => poll.id === editingPoll.id ? editingPoll : poll));
      } else {
        // Add new poll
        const newPoll = {
          ...editingPoll,
          id: Math.max(0, ...polls.map(p => p.id)) + 1
        };
        setPolls([...polls, newPoll]);
      }
      setShowEditForm(false);
      setEditingPoll(null);
    }
  };

  // Create new poll
  const handleCreatePoll = () => {
    setEditingPoll({
      id: null,
      title: "",
      options: [
        { id: 1, text: "", votes: 0 },
        { id: 2, text: "", votes: 0 }
      ]
    });
    setShowEditForm(true);
  };

  // Handle option text change in edit form
  const handleOptionTextChange = (optionId, text) => {
    setEditingPoll({
      ...editingPoll,
      options: editingPoll.options.map(opt => 
        opt.id === optionId ? { ...opt, text } : opt
      )
    });
  };

  // Add option to the poll being edited
  const handleAddOption = () => {
    const newOptionId = Math.max(0, ...editingPoll.options.map(o => o.id)) + 1;
    setEditingPoll({
      ...editingPoll,
      options: [...editingPoll.options, { id: newOptionId, text: "", votes: 0 }]
    });
  };

  // Remove option from the poll being edited
  const handleRemoveOption = (optionId) => {
    if (editingPoll.options.length > 2) {
      setEditingPoll({
        ...editingPoll,
        options: editingPoll.options.filter(opt => opt.id !== optionId)
      });
    }
  };

  // View poll results
  const handleViewResults = (poll, e) => {
    e && e.stopPropagation();
    setResultsPoll(poll);
    setShowPollResults(true);
  };

  // User Interface for selecting and answering polls
  const UserMode = () => (
    <div className="w-full max-w-3xl mx-auto p-4">
      {selectedPoll ? (
        <div className="bg-white p-6 rounded-lg shadow-md">
          <h2 className="text-xl font-bold mb-4">{selectedPoll.title}</h2>
          <div className="space-y-3">
            {selectedPoll.options.map(option => (
              <div key={option.id} className="flex items-center">
                <input
                  type="radio"
                  id={`option-${option.id}`}
                  name="poll-option"
                  className="mr-2"
                  checked={selectedOption === option.id}
                  onChange={() => setSelectedOption(option.id)}
                />
                <label htmlFor={`option-${option.id}`} className="text-lg">
                  {option.text}
                </label>
              </div>
            ))}
          </div>
          <button
            className="mt-6 px-4 py-2 bg-blue-500 text-white rounded hover:bg-blue-600 disabled:bg-gray-400"
            onClick={handleSubmit}
            disabled={selectedOption === null}
            type="button"
          >
            Відправити
          </button>
          <button
            className="mt-6 ml-2 px-4 py-2 bg-gray-300 text-gray-800 rounded hover:bg-gray-400"
            onClick={() => {
              setSelectedPoll(null);
              setSelectedOption(null);
            }}
            type="button"
          >
            Назад
          </button>
        </div>
      ) : (
        <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
          {polls.map(poll => (
            <div key={poll.id} className="bg-white p-4 rounded-lg shadow hover:shadow-md cursor-pointer transition-all" onClick={() => setSelectedPoll(poll)}>
              <h3 className="font-semibold text-lg">{poll.title}</h3>
              <p className="text-gray-500 mt-2">{poll.options.length} варіантів відповіді</p>
            </div>
          ))}
        </div>
      )}
      
      {/* Submit message popup */}
      {showSubmitMessage && (
        <div className="fixed inset-0 flex items-center justify-center bg-black bg-opacity-50">
          <div className="bg-white p-6 rounded-lg shadow-lg">
            <h3 className="text-xl font-bold text-green-600">Відповідь відправлено!</h3>
            <p className="mt-2">Дякуємо за вашу участь.</p>
          </div>
        </div>
      )}
    </div>
  );

  // Admin Interface for managing polls
  const AdminMode = () => (
    <div className="w-full max-w-4xl mx-auto p-4">
      {showEditForm ? (
        <div className="bg-white p-6 rounded-lg shadow-md">
          <h2 className="text-xl font-bold mb-4">
            {editingPoll.id ? "Редагувати опитування" : "Створити нове опитування"}
          </h2>
          <div className="mb-4">
            <label className="block text-sm font-medium mb-1">Заголовок опитування</label>
            <input
              type="text"
              className="w-full p-2 border rounded"
              value={editingPoll.title}
              onChange={(e) => setEditingPoll({...editingPoll, title: e.target.value})}
            />
          </div>
          
          <h3 className="font-medium mb-2">Варіанти відповідей:</h3>
          {editingPoll.options.map((option, index) => (
            <div key={option.id} className="flex items-center mb-2">
              <input
                type="text"
                className="flex-grow p-2 border rounded"
                value={option.text}
                placeholder={`Варіант ${index + 1}`}
                onChange={(e) => handleOptionTextChange(option.id, e.target.value)}
              />
              {editingPoll.options.length > 2 && (
                <button
                  className="ml-2 p-1 text-red-500"
                  onClick={() => handleRemoveOption(option.id)}
                  type="button"
                >
                  <Trash2 size={18} />
                </button>
              )}
            </div>
          ))}
          
          <button
            className="mt-2 px-3 py-1 text-sm bg-gray-100 rounded flex items-center hover:bg-gray-200"
            onClick={handleAddOption}
            type="button"
          >
            <Plus size={16} className="mr-1" /> Додати варіант
          </button>
          
          <div className="mt-6 flex justify-end">
            <button
              className="px-4 py-2 bg-gray-300 text-gray-800 rounded hover:bg-gray-400 mr-2"
              onClick={() => {
                setShowEditForm(false);
                setEditingPoll(null);
              }}
              type="button"
            >
              Скасувати
            </button>
            <button
              className="px-4 py-2 bg-blue-500 text-white rounded hover:bg-blue-600"
              onClick={handleSavePoll}
              disabled={!editingPoll.title || editingPoll.options.some(opt => !opt.text)}
              type="button"
            >
              Зберегти
            </button>
          </div>
        </div>
      ) : showPollResults ? (
        <div className="bg-white p-6 rounded-lg shadow-md">
          <h2 className="text-xl font-bold mb-4">Результати: {resultsPoll.title}</h2>
          
          <div className="flex flex-col md:flex-row md:space-x-4">
            <div className="md:w-1/2 mb-8 md:mb-0">
              <h3 className="font-medium mb-2">Кругова діаграма</h3>
              <div className="h-64">
                <ResponsiveContainer width="100%" height="100%">
                  <PieChart>
                    <Pie
                      data={resultsPoll.options}
                      nameKey="text"
                      dataKey="votes"
                      cx="50%"
                      cy="50%"
                      outerRadius={80}
                      fill="#8884d8"
                      label={({text, percent}) => `${text} ${(percent * 100).toFixed(0)}%`}
                    >
                      {resultsPoll.options.map((entry, index) => (
                        <Cell key={`cell-${index}`} fill={COLORS[index % COLORS.length]} />
                      ))}
                    </Pie>
                    <Tooltip formatter={(value) => [`${value} голосів`, 'Кількість']} />
                  </PieChart>
                </ResponsiveContainer>
              </div>
            </div>
            
            <div className="md:w-1/2">
              <h3 className="font-medium mb-2">Гістограма</h3>
              <div className="h-64">
                <ResponsiveContainer width="100%" height="100%">
                  <BarChart data={resultsPoll.options}>
                    <CartesianGrid strokeDasharray="3 3" />
                    <XAxis dataKey="text" tick={{fontSize: 12}} />
                    <YAxis />
                    <Tooltip formatter={(value) => [`${value} голосів`, 'Кількість']} />
                    <Bar dataKey="votes" fill="#8884d8">
                      {resultsPoll.options.map((entry, index) => (
                        <Cell key={`cell-${index}`} fill={COLORS[index % COLORS.length]} />
                      ))}
                    </Bar>
                  </BarChart>
                </ResponsiveContainer>
              </div>
            </div>
          </div>
          
          <div className="mt-8">
            <h3 className="font-medium mb-2">Детальна статистика:</h3>
            <table className="w-full border-collapse">
              <thead>
                <tr className="bg-gray-100">
                  <th className="p-2 text-left">Варіант відповіді</th>
                  <th className="p-2 text-right">Голоси</th>
                  <th className="p-2 text-right">Відсоток</th>
                </tr>
              </thead>
              <tbody>
                {resultsPoll.options.map(option => {
                  const totalVotes = resultsPoll.options.reduce((sum, opt) => sum + opt.votes, 0);
                  const percentage = totalVotes > 0 ? (option.votes / totalVotes * 100).toFixed(1) : 0;
                  
                  return (
                    <tr key={option.id} className="border-b">
                      <td className="p-2">{option.text}</td>
                      <td className="p-2 text-right">{option.votes}</td>
                      <td className="p-2 text-right">{percentage}%</td>
                    </tr>
                  );
                })}
                <tr className="font-semibold">
                  <td className="p-2">Всього</td>
                  <td className="p-2 text-right">
                    {resultsPoll.options.reduce((sum, opt) => sum + opt.votes, 0)}
                  </td>
                  <td className="p-2 text-right">100%</td>
                </tr>
              </tbody>
            </table>
          </div>
          
          <button
            className="mt-6 px-4 py-2 bg-gray-300 text-gray-800 rounded hover:bg-gray-400"
            onClick={() => {
              setShowPollResults(false);
              setResultsPoll(null);
            }}
            type="button"
          >
            Назад до списку
          </button>
        </div>
      ) : (
        <>
          <div className="flex justify-between items-center mb-6">
            <h2 className="text-xl font-bold">Керування опитуваннями</h2>
            <div className="flex space-x-2">
              <button 
                className="px-4 py-2 bg-green-500 text-white rounded flex items-center hover:bg-green-600"
                onClick={handleCreatePoll}
              >
                <Plus size={18} className="mr-1" /> Створити нове
              </button>
              
              <button 
                className="px-4 py-2 bg-blue-500 text-white rounded flex items-center hover:bg-blue-600"
                onClick={exportPolls}
              >
                <Download size={18} className="mr-1" /> Експорт JSON
              </button>
              
              <label className="px-4 py-2 bg-purple-500 text-white rounded flex items-center hover:bg-purple-600 cursor-pointer">
                <Upload size={18} className="mr-1" /> Імпорт JSON
                <input
                  type="file"
                  accept=".json"
                  className="hidden"
                  onChange={importPolls}
                />
              </label>
            </div>
          </div>
          
          <div className="overflow-x-auto">
            <table className="w-full border-collapse bg-white shadow rounded-lg">
              <thead>
                <tr className="bg-gray-100">
                  <th className="p-3 text-left">Заголовок</th>
                  <th className="p-3 text-center">Варіанти</th>
                  <th className="p-3 text-center">Всього голосів</th>
                  <th className="p-3 text-center">Дії</th>
                </tr>
              </thead>
              <tbody>
                {polls.map(poll => {
                  const totalVotes = poll.options.reduce((sum, opt) => sum + opt.votes, 0);
                  
                  return (
                    <tr key={poll.id} className="border-b hover:bg-gray-50">
                      <td className="p-3">{poll.title}</td>
                      <td className="p-3 text-center">{poll.options.length}</td>
                      <td className="p-3 text-center">{totalVotes}</td>
                      <td className="p-3 text-center">
                        <button 
                          className="p-1 text-blue-500 hover:text-blue-700 mr-2"
                          onClick={(e) => handleViewResults(poll, e)}
                          title="Переглянути результати"
                          type="button"
                        >
                          <div className="inline-block px-2 py-1 bg-blue-100 rounded">Результати</div>
                        </button>
                        <button 
                          className="p-1 text-gray-500 hover:text-gray-700 mr-2"
                          onClick={(e) => handleEditPoll(poll, e)}
                          title="Редагувати"
                          type="button"
                        >
                          <Edit size={18} />
                        </button>
                        <button 
                          className="p-1 text-red-500 hover:text-red-700"
                          onClick={(e) => handleDeletePoll(poll.id, e)}
                          title="Видалити"
                          type="button"
                        >
                          <Trash2 size={18} />
                        </button>
                      </td>
                    </tr>
                  );
                })}
              </tbody>
            </table>
          </div>
        </>
      )}
    </div>
  );

  return (
    <div className="min-h-screen bg-gray-100">
      {/* Header */}
      <header className="bg-blue-600 text-white shadow">
        <div className="container mx-auto px-4 py-4">
          <div className="flex flex-col sm:flex-row items-center justify-between">
            <h1 className="text-2xl font-bold mb-4 sm:mb-0">Соціологічне опитування</h1>
            
            <div className="tabs flex space-x-1 bg-blue-700 p-1 rounded-md">
              <button
                className={`flex items-center px-4 py-2 rounded-md transition-colors ${
                  activeMode === 'user' 
                    ? 'bg-white text-blue-600' 
                    : 'text-white hover:bg-blue-800'
                }`}
                onClick={() => {
                  setActiveMode('user');
                  setSelectedPoll(null);
                  setShowEditForm(false);
                  setShowPollResults(false);
                }}
              >
                <User size={18} className="mr-2" />
                Користувач
              </button>
              <button
                className={`flex items-center px-4 py-2 rounded-md transition-colors ${
                  activeMode === 'admin' 
                    ? 'bg-white text-blue-600' 
                    : 'text-white hover:bg-blue-800'
                }`}
                onClick={() => {
                  setActiveMode('admin');
                  setSelectedPoll(null);
                  setShowEditForm(false);
                  setShowPollResults(false);
                }}
              >
                <UserCog size={18} className="mr-2" />
                Адміністратор
              </button>
            </div>
          </div>
        </div>
      </header>

      {/* Main content */}
      <main className="container mx-auto py-8">
        {activeMode === 'user' ? <UserMode /> : <AdminMode />}
      </main>
      
      {/* Footer */}
      <footer className="bg-gray-800 text-white py-4 mt-10">
        <div className="container mx-auto px-4 text-center">
          <p>© 2025 Соціологічне опитування. Всі права захищені.</p>
        </div>
      </footer>
    </div>
  );
}