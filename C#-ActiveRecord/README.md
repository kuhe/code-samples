Code Sample (C#)

(Arguments for the validity, testability, and soundness of active record pattern aside...)

ActiveRecord overlay for Visual C# Entity Framework
==================

Define new class. Just add a method Initialize that sets the Model (DbSet<TEntity>) and the context.

    public partial class Score : ActiveRecord<Score>
    {
        protected override void Initialize()
        {
            FlashCardEntities context = new FlashCardEntities();
            Context = context;
            Model = context.Scores;
        }
    }
    
Subsequently, 

        IQueryable<Score> s = Scores.Get(); // get all
        IQueryable<Score> s = Scores.Get(2); // get by id
        IQueryable<Score> s = Scores.Get(x => x.UserName == "Student"); // get by lambda
        Score s = Scores.GetOne(x => x.StudentAnswer == 64); // GetOne convenience method
        
        s.Save(); // update
        s.Delete(); // delete
        s.Add(); // insert, returns a new object with new Id (necessitates inclusion of call to Persist())
        
        Score.Persist() // execute db update, same as SaveChanges()
