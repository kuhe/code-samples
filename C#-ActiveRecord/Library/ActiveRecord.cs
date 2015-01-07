using System;
using System.Linq;
using System.Linq.Expressions;

namespace WebApplication1.Library.Model
{
    public partial class ActiveRecord<T>
        /** type of the entity framework base class */
        where T : ActiveRecord<T>, new()
    {
        protected override void Initialize()
        {
            throw new Exception("You must set the static property DbSet to entities.TableName");
        }
        public T ToData()
        {
            return (T)this;
        }
        public static IQueryable<T> Get()
        {
            return Get(x => true);
        }
        public static IQueryable<T> Get(int id, bool justOne = false)
        {
            return Get(x => x.Id == id);
        }
        public static T GetOne()
        {
            return Get(x => true, true);
        }
        public static T GetOne(int id)
        {
            return Get(x => x.Id == id, true);
        }
        public static T GetOne(Expression<Func<T, bool>> predicate)
        {
            return Get(predicate, true);
        }
        public ActiveRecord<T> Add()
        {
            return Save(true);
        }
    }
}