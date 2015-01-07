using System;
using System.Data.Entity;
using JSON = System.Web.Helpers.Json;

namespace WebApplication1.Library.Model
{
    public abstract class DataObject<T> : IDataObjectBase<T>
        where T : DataObject<T>, new()
    {
        public int? Id { set; get; }
        public static T CreateInstance()
        {
            T newDataObject = new T();
            newDataObject.Initialize();
            return newDataObject;
        }
        protected abstract void Initialize();
        protected static DbContext Context;
        public static DbContext GetContext()
        {
            if (Context == null)
            {
                CreateInstance();
            }
            return Context;
        }
        public static DbContext SetContext(DbContext context)
        {
            Context = context;
            return context;
        }
        protected static DbSet<T> Model;
        public static DbSet<T> GetModel()
        {
            if (Model == null)
            {
                CreateInstance();
            }
            return Model; 
        }
        public static DbSet<T> SetModel(DbSet<T> model)
        {
            Model = model;
            return Model;
        }
    }
}