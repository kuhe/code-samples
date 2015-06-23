using System;
using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Linq.Expressions;

namespace WebApplication1.Library.Model
{
    public class ActiveRecord<T> : DataObject<T>
        where T : ActiveRecord<T>, new()
    {
        #region core
        public static IQueryable<T> Get(Expression<Func<T, bool>> predicate)
        {
            DbSet<T> query = Model;
            IQueryable<T> items = query.Where(predicate);
            return items;
        }
        public T Save(bool insert = false)
        {
            T data = (T) this;
            if (insert || data.Id == null)
            {
                Model.Add(data);
                Context.Entry(data).State = EntityState.Added;
                Persist();
                T newObject = (T)Context.Entry(data).GetDatabaseValues().ToObject();
                Model.Attach(data);
                return newObject;
            }
            Model.Attach(data);
            Context.Entry(data).State = EntityState.Modified;
            return (T)this;
        }
        public bool Delete()
        {
            T data = (T) this;
            Model.Remove(data);
            Context.Entry(data).State = EntityState.Deleted;
            return true;
        }
        public static void Persist()
        {
            // can we make this automatic?
            Context.SaveChanges();
        }
        ~ActiveRecord()
        {
            // Context.SaveChanges();
        }
        #endregion
        #region secondary
        public IDataObjectBase Ingest(IDataObjectBase input)
        {
            return (T) input;
        }
        protected override void Initialize()
        {
            throw new Exception("You must set the static property DbSet to entities.TableName");
        }
        public static IQueryable<T> Get()
        {
            return Get(x => true);
        }
        public static IQueryable<T> Get(int id)
        {
            return Get(x => x.Id == id);
        }
        private static T Get(Expression<Func<T, bool>> predicate, bool justOne)
        {
            DbSet<T> query = Model;
            T result = query.FirstOrDefault<T>(predicate);
            return result;
        }
        public static T GetOne()
        {
            return Get(x => true, true);
        }
        public static T GetOne(int? id)
        {
            if (id == null)
            {
                return GetOne();
            }
            return Get(x => x.Id == id, true);
        }
        public static T GetOne(Expression<Func<T, bool>> predicate)
        {
            return Get(predicate, true);
        }
        public T Add()
        {
            return Save(true);
        }
        #endregion
    }
}