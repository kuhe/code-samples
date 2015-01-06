using System;
using System.Collections.Generic;
using System.Data.Entity;
using JSON = System.Web.Helpers.Json;

namespace WebApplication1.Library.Model
{
    public abstract class DataObject<T> : IDataObjectBase<T>
        where T : DataObject<T>, new()
    {
        public int? Id { set; get; }
        public T Ingest(DataObject<T> dataObject)
        {
            throw new Exception("Implement in ActiveRecord");
        } 
        public static T CreateInstance()
        {
            T newDataObject = new T();
            newDataObject.Initialize();
            return newDataObject;
        }
        protected abstract void Initialize();
        protected static DbContext Db = null;
        public static DbContext GetDb()
        {
            if (Db == null)
            {
                CreateInstance();
            }
            return Db;
        }
        public static DbContext SetDb(DbContext db)
        {
            Db = db;
            return Db;
        }
        protected static DbSet<T> Model = null;
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
        protected DataObject()
        {
        }
        protected DataObject(T type)
        {
        }
    }
}