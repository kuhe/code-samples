using System.Data.Entity;
using JSON = System.Web.Helpers.Json;

namespace WebApplication1.Library.Model
{
    public abstract class DataObject<T> : IDataObjectBase
        where T : DataObject<T>, new()
    {
        public int? Id { get; set; }
        private static void CreateInstance()
        {
            T newDataObject = new T();
            newDataObject.Initialize();
        }
        protected abstract void Initialize();
        private static DbContext _context;
        protected static DbContext Context
        {
            get
            {
                if (_context == null)
                {
                    CreateInstance();
                }
                return _context;
            }
            set { _context = value; }
        }

        private static DbSet<T> _model;
        protected static DbSet<T> Model
        {
            get
            {
                if (_model == null)
                {
                    CreateInstance();
                }
                return _model;
            }
            set { _model = value; }
        }
    }
}