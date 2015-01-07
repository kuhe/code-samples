
namespace WebApplication1.Library.Model
{
    public interface IDataObjectBase<T>
        where T : DataObject<T>, new()
    {
        int? Id { get; set; }
    }
}