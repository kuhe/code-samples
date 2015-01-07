using System;
using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Linq.Expressions;

namespace WebApplication1.Library.Model
{
    public partial class ActiveRecord<T> : DataObject<T>
        where T : ActiveRecord<T>, new()
    {
        public static IQueryable<T> Get(Expression<Func<T, bool>> predicate)
        {
            DbSet<T> query = GetModel();
            IQueryable<T> items = query.Where(predicate);
            return items;
        }
        public static T Get(Expression<Func<T, bool>> predicate, bool justOne)
        {
            DbSet<T> query = GetModel();
            T result = query.FirstOrDefault<T>(predicate);
            GetModel().Attach(result);
            return result;
        }
        public ActiveRecord<T> Save(bool insert = false)
        {
            T data = ToData();
            if (insert || data.Id == null)
            {
                data.Id = null;
                GetModel().Add(data);
                GetContext().Entry(data).State = EntityState.Added;
            }
            else
            {
                GetContext().Set<T>().Attach(data);
                GetContext().ChangeTracker.Entries<T>().First(e => e.Entity == data).State = EntityState.Modified;
            }
            GetContext().SaveChanges();
            return this;
        }
        public bool Delete()
        {
            return true;
        }
    }
}